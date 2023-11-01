#include "pidcontroller.h"

#include <Arduino.h>


PidController::PidController() {}


PidController::PidController(float Kp, float Ki, float Kd, float dt) {

    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->dt = dt;

    this->derr = 0.0f;
    this->ierr = 0.0f;

}


float PidController::update(float target, float curr) {

    // Check for infinities and NaNs and return NaN if they are found.
    if (isnan(target) || isnan(curr) || isinf(target) || isinf(curr)) {

        return NAN;

    }

    float err = target - curr;
    
    this->ierr += err * dt;

    float response = this->Kp * err + this->Ki * this->ierr + (err - this->derr) / this->dt;

    this->derr = err;

    Serial.print("Kp: ");
    Serial.print(this->Kp);
    Serial.print(" Ki: ");
    Serial.print(this->Ki);
    Serial.print(" Kd: ");
    Serial.print(this->Kd);
    Serial.print(" dt: ");
    Serial.print(this->dt);
    Serial.print(" target: ");
    Serial.print(target);
    Serial.print(" curr: ");
    Serial.print(curr);
    Serial.print(" response: ");
    Serial.println(response);

    return response;

}


void PidController::reset() {

    this->derr = 0;
    this->ierr = 0;

}