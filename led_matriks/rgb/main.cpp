#include <signal.h>
#include <stdlib.h>
#include <iostream>

#include "ws2812.h"

using namespace std;

void delay(int ms){
  usleep(ms*1000);
}

int  main(void)
{
  // Objekt anlegen und LEDs initialisieren
  WS2812 leds;
  leds.reset();
  leds.setup(1);
  leds.init();

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

  return 0;
}
