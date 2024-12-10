#include <unistd.h>
#include <iostream>
#include <string>
#include <signal.h>
#include <stdlib.h>

#include "MFRC522.h"
#include "ws2812.h"

using namespace std;

void delay(int ms){
  usleep(ms*1000);
}

int main(){
  MFRC522 mfrc;
  WS2812 leds;

  mfrc.PCD_Init();
  leds.reset();
  leds.setup(1);
  leds.init();

  while(true){
    // Look for a card
    if(mfrc.PICC_IsNewCardPresent()){
      // Try to read the serial...
      if(mfrc.PICC_ReadCardSerial()){
        // Output the serial
        string id = mfrc.uid.ToString();
        cout << id << endl << flush;

        // Rot
        leds.fill(1, 0xFF0000);
        leds.render();
        delay(1000);

        // Grün
        leds.fill(1, 0x00FF00);
        leds.render();
        delay(1000);

        // Blaue Streifen
        leds.fill(1, 0x0000FF, 0, 8);
        leds.fill(1, 0x0000FF, 16, 8);
        leds.fill(1, 0x0000FF, 32, 8);
        leds.fill(1, 0x0000FF, 48, 8);
        leds.render();
        delay(1000);

        // Löschen
        leds.fill(1, 0);
        leds.render();
        delay(1000);

        // Random einzeln
        for(int i =0; i<64; i++){
          leds.random(1,i,1);
          leds.render();
          delay(100);
        }

        // Random alle
        for(int i =0; i<64; i++){
          leds.random(1);
          leds.render();
          delay(10);
        }

        // Löschen
        leds.fill(1,0);
        leds.render();

        delay(1000);
      }
    }
  }

  return 0;
}