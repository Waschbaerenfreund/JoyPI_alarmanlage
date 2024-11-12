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
#include <wiringPi.h>

#include "MFRC522.h"
const string richtiger_chip = "platzhalter";

using namespace std;

void delay(int ms){
  usleep(ms*1000);
}

int main(){
  MFRC522 mfrc;

  mfrc.PCD_Init();

  while(true){
    // Look for a card
    if(mfrc.PICC_IsNewCardPresent()){

      // Try to read the serial...
      if(mfrc.PICC_ReadCardSerial()){

        // Output the serial
        string id = mfrc.uid.ToString();
        cout << id << endl << flush;

        delay(1000);
      }
    }
  }

  return 0;
}
