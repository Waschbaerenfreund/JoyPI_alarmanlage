#include <unistd.h>
#include <iostream>
#include <string>

#include "MFRC522.h"

using namespace std;
const string karte = "5B1F8D73";

void delay(int ms){
    usleep(ms * 1000);
}

bool rfid_kontrolle(MFRC522 &mfrc);
bool watchdog();
bool machen_wir_alarm();

int main(){
    MFRC522 mfrc;
    mfrc.PCD_Init();

    while(true){
        if (rfid_kontrolle(mfrc)) {
            cout << "Karte erkannt!" << endl;
            // Anlage ein oder mit button matrix
            if(true){
                cout << "Anlage wird eingeschaltet" << endl;
                //watchdog() funktion leuft im loop bis neuer chip erkannt wird oder alarm ausgelöst wird
                //countdown() auf lcd countdown zum deaktieveren 
                //alarm_alarm() alarm mit allem was dazugehört bis es mit anderem code deaktviert wird
                

            } else {
                cout << "Anlage wird ausgeschaltet" << endl;
            }


        }
        delay(100); // Reduziere CPU-Auslastung


    }
    return 0;
}

bool rfid_kontrolle(MFRC522 &mfrc)
{
    bool ergebniss = false;

    // Look for a card
    if (mfrc.PICC_IsNewCardPresent())
    {
        // Try to read the serial...
        if (mfrc.PICC_ReadCardSerial())
        {
            // Output the serial
            string id = mfrc.uid.ToString();
            if (id == karte)
            {
                ergebniss = true; // Setze auf true statt 1
            }
            delay(1000);
        }
    }
    return ergebniss;
}


bool watchdog()
{
    while (true)
    {
        if (machen_wir_alarm())
        {
            /* code */
        }
        
    }
    
}

bool machen_wir_alarm()
{
    
}