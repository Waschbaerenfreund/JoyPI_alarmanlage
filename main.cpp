#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <wiringPi.h>
#include "MFRC522.h"

using namespace std;

const string karte = "5B1F8D73";
const int gpioPin = 26; // GPIO-Pin 26
atomic<bool> alarm_ausgelöst(false); // Atomare Variable für den Alarmstatus

void delay(int ms) {
    usleep(ms * 1000);
}

bool rfid_kontrolle(MFRC522 &mfrc);
bool watchdog();
bool machen_wir_alarm();

int main() {
    MFRC522 mfrc;
    mfrc.PCD_Init();

    // GPIO initialisieren
    wiringPiSetupGpio(); // Verwende BCM-Pin-Nummerierung
    pinMode(gpioPin, INPUT); // Setze Pin 26 als Eingang

    // Starte den Watchdog in einem separaten Thread
    thread watchdog_thread(watchdog);

    while (true) {
        if (rfid_kontrolle(mfrc)) {
            cout << "Karte erkannt!" << endl;

            // Anlage ein oder mit button matrix
            if (true) { // Hier sollte die Bedingung für das Einschalten der Anlage stehen
                cout << "Anlage wird eingeschaltet" << endl;

                // Setze den Alarmstatus zurück, wenn die Anlage eingeschaltet wird
                alarm_ausgelöst = false;
            } else {
                cout << "Anlage wird ausgeschaltet" << endl;
            }
        }
        delay(100); // Reduziere CPU-Auslastung
    }

    // Warten auf den Watchdog-Thread (in diesem Beispiel wird der Thread nie beendet)
    watchdog_thread.join();
    return 0;
}

bool rfid_kontrolle(MFRC522 &mfrc) {
    bool ergebniss = false;

    // Look for a card
    if (mfrc.PICC_IsNewCardPresent()) {
        // Try to read the serial... 
        if (mfrc.PICC_ReadCardSerial()) {
            // Output the serial
            string id = mfrc.uid.ToString();
            if (id == karte) {
                ergebniss = true; // Setze auf true statt 1
            }
            delay(1000);
        }
    }
    return ergebniss;
}

bool watchdog() {
    while (true) {
        if (machen_wir_alarm()) {
            cout << "Alarm ausgelöst!" << endl;
            alarm_ausgelöst = true; // Setze den Alarmstatus auf true
            // Hier könnte zusätzlicher Code für den Alarm hinzugefügt werden
        }
        delay(500); // Wartezeit zwischen den Überprüfungen
    }
}

bool machen_wir_alarm() {
    // Lese den Wert des GPIO-Pins 26
    int value = digitalRead(gpioPin); // Lese den aktuellen Wert des Pins

    return (value == LOW); // Alarm auslösen, wenn der Wert LOW ist (Ground)
}
