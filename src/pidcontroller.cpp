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

    float err = target - curr;
    
    this->ierr += err * dt;

    float response = this->Kp * err + this->Ki * this->ierr + (err - this->derr) / this->dt;

    this->derr = err;

    return response;

}


void PidController::reset() {

    this->derr = 0;
    this->ierr = 0;

}