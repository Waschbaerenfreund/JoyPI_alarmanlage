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

// 
#include <unistd.h>
#include <iostream>
#include <string>
#include <wiringPi.h>

#include "MFRC522.h"
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

