#include <unistd.h>
#include <iostream>
#include <string>
#include <wiringPi.h>
#include "MFRC522.h"
#include "ws2812.h"

using namespace std;

const string karte = "5B1F8D73";
const int BEWEGUNGSMELDER_PIN = 23; // Anpassen an den tatsächlichen Pin des Bewegungsmelders
const int LED_COUNT = 1; // Anzahl der LEDs

WS2812 leds;

void delay(int ms) {
    usleep(ms * 1000);
}

bool rfid_kontrolle(MFRC522 &mfrc);
bool watchdog(MFRC522 &mfrc);
bool machen_wir_alarm();
void countdown();
void alarm_alarm();

int main() {
    wiringPiSetup(); // Initialisiere wiringPi
    
    leds.reset();
    leds.setup(LED_COUNT);
    leds.init();

    MFRC522 mfrc;
    mfrc.PCD_Init();

    bool anlage_aktiv = false;

    while(true) {
        if (rfid_kontrolle(mfrc)) {
            cout << "Karte erkannt!" << endl;
            
            if (!anlage_aktiv) {
                cout << "Anlage wird eingeschaltet" << endl;
                anlage_aktiv = true;
                countdown();
                while (rfid_kontrolle(mfrc))
                {
                    if (watchdog()) 
                    {
                        alarm_alarm();
                    }                
                }
                

            } else {
                cout << "Anlage wird ausgeschaltet" << endl;
                anlage_aktiv = false;
            }
        }
        delay(100); // Reduziere CPU-Auslastung
    }
    return 0;
}

bool rfid_kontrolle(MFRC522 &mfrc) {
    bool ergebnis = false;

    if (mfrc.PICC_IsNewCardPresent()) {
        if (mfrc.PICC_ReadCardSerial()) {
            string id = mfrc.uid.ToString();
            if (id == karte) {
                ergebnis = true;
            }
            delay(1000);
        }
    }
    return ergebnis;
}

bool watchdog()
{
        if (machen_wir_alarm()) {
            leds.fill(LED_COUNT, 0xFF0000);
            leds.render();
            delay(500);
            leds.fill(LED_COUNT, 0x00FF00);
            leds.render();
            delay(500);

            if (rfid_kontrolle(mfrc)) {
                return false;
            }
        }   
    return true; // Alarm wurde ausgelöst
}

bool machen_wir_alarm() {
    int bewegung = digitalRead(BEWEGUNGSMELDER_PIN);
    if (bewegung == HIGH) {
        cout << "Bewegung erkannt!" << endl;
        return true;
    }

    return false;
}

void countdown() {
    // Implementieren Sie hier den Countdown
    cout << "Countdown gestartet..." << endl;
    // Beispiel: 10 Sekunden Countdown
    for (int i = 10; i > 0; i--) {
        cout << i << "..." << endl;
        delay(1000);
    }
    cout << "Anlage aktiviert!" << endl;
}

void alarm_alarm() {
    cout << "ALARM! ALARM!" << endl;
    // Implementieren Sie hier die Alarmlogik
    while (true) {
        leds.fill(LED_COUNT, 0xFF0000); // Rot
        leds.render();
        delay(500);
        leds.fill(LED_COUNT, 0x0000FF); // Blau
        leds.render();
        delay(500);
        // Hier könnte man einen Piepton oder andere Alarmaktionen hinzufügen
        // Überprüfen Sie hier auch, ob der Alarm deaktiviert werden soll
    }
}