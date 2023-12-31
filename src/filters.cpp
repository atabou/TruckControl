#include "filters.h"

#include <Arduino.h>


IIRFilter::IIRFilter() {

    this->alpha = 0.0f;
    this->prev = 0.0f;

}


IIRFilter::IIRFilter(float alpha) {

    this->alpha = alpha;
    this->prev = 0.0f;

}


float IIRFilter::pass(float curr) {

    this->prev = this->alpha * curr + (1.0f - this->alpha) * this->prev;
    
    Serial.print(">Filtered: "); Serial.println(this->prev);
    
    return this->prev;

}


void IIRFilter::reset() {

    this->prev = 0.0f;

}