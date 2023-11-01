#include "bldc.h"


BldcMotor::BldcMotor() {

    this->enabled = false;

}


BldcMotor::BldcMotor(uint8_t pin) {
    
    // Initialize variables
    this->pin = pin;
    this->pwm = BLDC_MOTOR_ZERO_PWM;
    this->enabled = false;
    this->changed = false;

    // Connect Pin
    this->bldc.attach(pin);
    this->bldc.writeMicroseconds(this->pwm);
    
}


void BldcMotor::setPWM(int pwm) {

    // Set the pwm and mark the value as changed for the
    // next time the motor is run.
    this->pwm = pwm;
    this->changed = true;

}


void BldcMotor::start() {

    this->enabled = true;

}


void BldcMotor::run() {

    // If the motor is enabled and the pwm has changed
    // since the last time the motor was run, then
    // write the new pwm value to the motor.
    if (this->enabled && this->changed) {

        this->bldc.writeMicroseconds(this->pwm);
        this->changed = false;

    }

}


void BldcMotor::stop() {
 
    this->pwm = BLDC_MOTOR_ZERO_PWM;
    this->bldc.writeMicroseconds(this->pwm);
    this->enabled = false;
    this->changed = false;

}
