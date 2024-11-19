#include <unistd.h>
#include <iostream>
#include <string>

#include "MFRC522.h"

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
