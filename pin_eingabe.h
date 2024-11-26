#ifndef PIN_EINGABE_H
#define PIN_EINGABE_H

#include <string>

class PinEingabe {
public:
    PinEingabe();
    bool pinEingeben(const std::string& pin);
    bool pinValidieren(const std::string& pin);
    void pinZuruecksetzen();
    void setup();
    void loop();
    bool checkCode(const char* correctCode);

private:
    std::string aktuellerPin;
    const std::string korrekterPin = "1234"; // Beispiel-PIN, sollte sicher gespeichert werden
};

#endif // PIN_EINGABE_H