/*
int eingabe_zum_scharfschalten()
{
1. rfid  --> wenn ok --> codeabfrage()
--> abfrage ob deaktivieren oder aktivieren
--> aktivieren --> alarm_outputs_config()
--> deaktivieren,alarm_outputs_abschalten() 

}
int codeabfrage()
{   
    abfrage eingabe (4 digits)
    3 mal eingeben falsch --> alarmanlage löst aus
}

masterpin zum deaktivieren des alarms
*/
#include <unistd.h>
#include <iostream>
#include <string>

#include "MFRC522.h"
#include "pin_eingabe.h" // Annahme: Diese Header-Datei enthält die Deklaration der Funktion in pin_eingabe.cpp

const string richtiger_chip = "platzhalter";

using namespace std;

void delay(int ms){
  usleep(ms*1000);
}

int rfid_kontrolle()
{
  MFRC522 mfrc;

  mfrc.PCD_Init();

  while(true)
  {
    // Look for a card
    if(mfrc.PICC_IsNewCardPresent()){


        // Output the serial
        string id = mfrc.uid.ToString();
        if( id == richtiger_chip)
        {
            //ausgabe auf lcd "rfid korrekt, bitte code eingeben"
            cout <<id <<endl;
            cout << "RFID korrekt, bitte Code eingeben" << endl;
            return 1;
        }

        delay(1000);
      }
    }
    return 0;
  }

int codeabfrage()
{
    // zähler für 3 durchläufe oder ne schleife
    return 0;
}
int eingabe_zum_scharfschalten()
{
    if(rfid_kontrolle())
    {
        if(codeabfrage())
        {
            // abfrage ob aktiviern oder deaktivieren
        }
    }
}

int main() {
    while (true) {
        // Aufruf der Funktion aus pin_eingabe.cpp
        int result = pin_eingabe(); // Annahme: pin_eingabe() ist die Funktion, die getestet werden soll

        // Ausgabe des Ergebnisses
        cout << "Ergebnis der Pin-Eingabe: " << result << endl;

        // Kurze Verzögerung, um die Schleife nicht zu schnell laufen zu lassen
        delay(1000);
    }

    return 0;
}
