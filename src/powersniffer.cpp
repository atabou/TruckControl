#include "powersniffer.h"

#include "common.h"

#include <Arduino.h>


#define DEFAULT_BIAS 0.25


PowerSniffer::PowerSniffer(int leftPin, int rightPin) {

    // Save the pin values.
    this->leftPin  = leftPin;
    this->rightPin = rightPin;
    this->bias = DEFAULT_BIAS;

    // Initialize the pins
    pinMode(this->leftPin, INPUT);
    pinMode(this->rightPin, INPUT);

}


float PowerSniffer::getReading() {

    int lraw = analogRead(this->leftPin);
    int rraw = analogRead(this->rightPin);

    // Convert the raw values to voltage values
    // 5V * 5.7V = 28.5V
    float lvolts = map_to_interval((float) lraw, 0.0f, 1023.0f, 0.0f, 28.5f);
    float rvolts = map_to_interval((float) rraw, 0.0f, 1023.0f, 0.0f, 28.5f);

    Serial.print(">lvolts: "); Serial.println(lvolts);
    Serial.print(">rvolts: "); Serial.println(rvolts);

    // Get the output reading
    return log(lvolts + this->bias) - log(rvolts + this->bias);
    
}


void PowerSniffer::setBias(float bias) {

    this->bias = bias;

}