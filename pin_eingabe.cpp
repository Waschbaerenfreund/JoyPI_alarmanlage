#include <wiringPi.h>
#include <iostream>
#include <cstring>

// Define the rows and columns for the 4x4 button matrix
const int ROWS = 4;
const int COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

int rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
int colPins[COLS] = {5, 4, 3, 2}; // Connect to the column pinouts of the keypad

char inputCode[5]; // Array to store the input code
int inputIndex = 0; // Index for the input code array

void setup() {
    wiringPiSetup();
    
    // Initialize the row pins as outputs and set them to HIGH
    for (int i = 0; i < ROWS; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
    }
    
    // Initialize the column pins as inputs with pull-up resistors
    for (int i = 0; i < COLS; i++) {
        pinMode(colPins[i], INPUT);
        pullUpDnControl(colPins[i], PUD_UP);
    }
}

char getKey() {
    for (int row = 0; row < ROWS; row++) {
        digitalWrite(rowPins[row], LOW); // Set the current row to LOW
        
        for (int col = 0; col < COLS; col++) {
            if (digitalRead(colPins[col]) == LOW) {
                while (digitalRead(colPins[col]) == LOW); // Wait for the key to be released
                digitalWrite(rowPins[row], HIGH); // Set the row back to HIGH
                return keys[row][col]; // Return the key value
            }
        }
        
        digitalWrite(rowPins[row], HIGH); // Set the row back to HIGH
    }
    
    return NO_KEY; // Return NO_KEY if no key is pressed
}
#define NO_KEY '\0'

void loop() {
    char key = getKey();
    if (key != NO_KEY) {
        std::cout << "Key pressed: " << key << std::endl;
        
        if (key == '#') {
            // If '#' is pressed, reset the input code
            inputIndex = 0;
            memset(inputCode, 0, sizeof(inputCode));
            std::cout << "Code reset" << std::endl;
        } else if (key == '*') {
            // If '*' is pressed, submit the code
            inputCode[inputIndex] = '\0'; // Null-terminate the string
            std::cout << "Code entered: " << inputCode << std::endl;
            inputIndex = 0; // Reset the index for the next input
        } else {
            // Store the key in the input code array
            if (inputIndex < 4) {
                inputCode[inputIndex] = key;
                inputIndex++;
            }
        }
    }
}
bool checkCode(const char* correctCode) {
    if (strcmp(inputCode, correctCode) == 0) {
        std::cout << "Correct code entered!" << std::endl;
        return true;
    } else {
        std::cout << "Incorrect code. Try again." << std::endl;
        return false;
    }
}

int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}