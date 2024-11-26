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

int main(){
    MFRC522 mfrc;
    mfrc.PCD_Init();

    while(true){
        if (rfid_kontrolle(mfrc)) {
            cout << "Karte erkannt!" << endl;
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
