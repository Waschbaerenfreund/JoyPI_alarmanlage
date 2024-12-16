#include <unistd.h>
#include <iostream>
#include <string>
#include <wiringPi.h>
#include "MFRC522.h"
#include "ws2812.h"

using namespace std;

const string karte1 = "5B1F8D73"; // Hauptkarte
const string karte2 = "8A2C7E45"; // Ersatzkarte
const int BEWEGUNGSMELDER_PIN = 23;
const int LED_COUNT = 1;
bool alarm_aktiv = false;

WS2812 leds;

void delay(int ms) {
    usleep(ms * 1000);
}

bool rfid_kontrolle(MFRC522 &mfrc, const string &karte);
void ueberwachung(MFRC522 &mfrc);
bool bewegung_erkannt();
void countdown();
void alarm_auslosen();
void alarm_deaktivieren(MFRC522 &mfrc);
bool pin_pruefen(int versuche, int pin_laenge);

int main() {
    if (wiringPiSetup() == -1) {
        cout << "WiringPi Setup fehlgeschlagen. Beende Programm." << endl;
        return 1;
    }
    
    leds.reset();
    leds.setup(LED_COUNT);
    leds.init();

    MFRC522 mfrc;
    if (!mfrc.PCD_Init()) {
        cout << "RFID-Leser Initialisierung fehlgeschlagen. Beende Programm." << endl;
        return 1;
    }

    bool anlage_aktiv = false;

    while (true) {
        if (rfid_kontrolle(mfrc, karte1)) {
            cout << "Karte erkannt!" << endl;
            
            if (!anlage_aktiv) {
                cout << "Anlage wird eingeschaltet" << endl;
                anlage_aktiv = true;
                countdown();
                ueberwachung(mfrc);
            } else {
                cout << "Anlage wird ausgeschaltet" << endl;
                anlage_aktiv = false;
                alarm_deaktivieren(mfrc);
            }
        }
        delay(100);
    }
    return 0;
}

bool rfid_kontrolle(MFRC522 &mfrc, const string &karte) {
    if (mfrc.PICC_IsNewCardPresent() && mfrc.PICC_ReadCardSerial()) {
        string id = mfrc.uid.ToString();
        if (id == karte) {
            delay(1000);
            return true;
        }
    }
    return false;
}

void ueberwachung(MFRC522 &mfrc) {
    while (true) {
        if (bewegung_erkannt()) {
            alarm_auslosen();
            while (alarm_aktiv) {
                if (rfid_kontrolle(mfrc, karte1)) {
                    alarm_deaktivieren(mfrc);
                    return;
                }
                delay(100);
            }
        }
        if (rfid_kontrolle(mfrc, karte1)) {
            return;  // Beende Überwachung, wenn RFID-Karte erkannt wird
        }
        delay(100);
    }
}

bool bewegung_erkannt() {
    return digitalRead(BEWEGUNGSMELDER_PIN) == HIGH;
}

void countdown() {
    cout << "Countdown gestartet..." << endl;
    for (int i = 10; i > 0; i--) {
        cout << i << "..." << endl;
        delay(1000);
    }
    cout << "Anlage aktiviert!" << endl;
}

void alarm_auslosen() {
    cout << "ALARM! ALARM!" << endl;
    alarm_aktiv = true;
}

void alarm_deaktivieren(MFRC522 &mfrc) {
    int versuche = 0;

    while (versuche < 3) { // Maximal drei Versuche für den PIN
        cout << "Bitte geben Sie den 4-stelligen PIN ein: ";
        if (pin_pruefen(versuche, 4)) { // Prüft den PIN
            alarm_aktiv = false;
            leds.fill(LED_COUNT, 0x000000); // LEDs ausschalten
            leds.render();
            cout << "Alarm deaktiviert." << endl;
            return;
        } else {
            versuche++;
            cout << "Falscher PIN! Noch " << (3 - versuche) << " Versuche übrig." << endl;
        }
    }

    // Nach drei Fehlversuchen
    cout << "Zu viele Fehlversuche! Alarm bleibt aktiv." << endl;

    while (true) { // Nur mit Ersatzkarte und 6-stelligem PIN deaktivierbar
        if (rfid_kontrolle(mfrc, karte2)) { 
            cout << "Ersatzkarte erkannt! Bitte geben Sie den 6-stelligen PIN ein: ";
            if (pin_pruefen(0, 6)) { // Prüft den neuen PIN
                alarm_aktiv = false;
                leds.fill(LED_COUNT, 0x000000); // LEDs ausschalten
                leds.render();
                cout << "Alarm mit Ersatzkarte deaktiviert." << endl;
                return;
            } else {
                cout << "Falscher PIN! Alarm bleibt aktiv." << endl;
            }
        } else {
            cout << "Warten auf Ersatzkarte..." << endl;
            delay(3000);
        }
    }
}

bool pin_pruefen(int versuche, int pin_laenge) {
    string korrekter_pin = (pin_laenge == 4) ? "1234" : "654321"; // Beispiel-PINs
    string eingabe;

    cin >> eingabe;

    if (eingabe.length() == pin_laenge && eingabe == korrekter_pin) {
        return true; // Richtiger PIN
    }

    return false; // Falscher PIN
}
