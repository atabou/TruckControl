#include "steeringservo.h"

#include "common.h"

#include <Arduino.h>

SteeringServo::SteeringServo(uint8_t pin, float target, float Kp, float Ki, float Kd, float dt) {

    // Initialize variables
    this->pin = pin;
    this->pwm = STEERING_SERVO_CENTERED_PWM;
    this->target = saturate(target, -STEERING_SERVO_MAX_DEG, STEERING_SERVO_MAX_DEG);
    this->ps = PowerSniffer(POWER_SNIFFING_LEFT_COIL_PIN, POWER_SNIFFING_RIGHT_COIL_PIN);
    this->pid = PidController(Kp, Ki, Kd, dt);
    this->autoSteerEnabled = false;
    this->filter = IIRFilter(FILTER_ALPHA);

    // Connect pin
    this->servo.attach(this->pin);
    this->servo.writeMicroseconds(this->pwm);

}

void SteeringServo::setPWM(int pwm) {

    this->pwm = pwm;
    this->servo.writeMicroseconds(this->pwm);

}


void SteeringServo::enableAutoSteer() {

    this->autoSteerEnabled = true;
    this->pid.reset();

}

unsigned long lastTime = 0;

void SteeringServo::run() {

    if (this->autoSteerEnabled && millis() - lastTime >= this->pid.dt) {

        // Perform Reading
        float curr = this->ps.getReading();
        Serial.print(">Current: "); Serial.println(curr);

        // Filter response
        float filtered = this->filter.pass(curr);
        Serial.print(">Filtered: "); Serial.println(filtered);

        // Perform PID Update
        float response = this->pid.update(this->target, filtered);
        Serial.print(">PID: "); Serial.println(response);

        // Convert angle in degrees to PWM
        this->pwm = (int) map_to_interval(
            response, 
            -STEERING_SERVO_MAX_DEG, 
            STEERING_SERVO_MAX_DEG, 
            STEERING_SERVO_MAX_LEFT_PWM, 
            STEERING_SERVO_MAX_RIGHT_PWM
        );

        Serial.print(">PWM: "); Serial.println(this->pwm);

        // Set output PWM
        this->servo.writeMicroseconds(this->pwm);

        // Update last time
        lastTime = millis();

    }


}


void SteeringServo::setAutoSteerGains(float Kp, float Ki, float Kd) {

    this->pid.Kp = Kp;
    this->pid.Ki = Ki;
    this->pid.Kd = Kd;
    this->pid.reset();

}


void SteeringServo::setTarget(float target) {

    this->target = target;

}


void SteeringServo::disableAutoSteer() {

    this->autoSteerEnabled = false;

}

