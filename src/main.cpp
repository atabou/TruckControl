#include <Arduino.h>

#include "common.h"
#include "bldc.h"
#include "steeringservo.h"

unsigned long terminalElapsedTime = 0;

void processCommand(String command);
void checkSerialEvent();

BldcMotor bldc;
SteeringServo steering;

void setup() {

    Serial.begin(9600);

    delay(100);

    steering = SteeringServo(STEERING_SERVO_PWM_PIN, 0, 0, 0, 0, POWER_SNIFFING_CONTROL_SAMPLE_TIME_MS);

    bldc  = BldcMotor(BLDC_MOTOR_PWM_PIN);

    Serial.println(steering.pwm);

}

void loop() {

    steering.run();
    
    bldc.run();

    checkSerialEvent();

}


void checkSerialEvent() {

    if (millis() - terminalElapsedTime > 1000) {
        
        if(Serial.available()) {

            String cmd = Serial.readStringUntil('\n');

            Serial.println(cmd);

            processCommand(cmd);
            
        }

        terminalElapsedTime = millis();

    }

}


void processCommand(String command) {

    command.trim();

    if (command.equals("as")) {
        
        if (steering.autoSteerEnabled) {

            steering.disableAutoSteer();
        
        } else {
        
            steering.enableAutoSteer();
        
        }

    } else if (command.equals("sm")) {
    
        // Start Motor
        if (bldc.enabled) {
        
            bldc.stop();
        
        } else {

            bldc.start();

        }
    
    } else if (command.startsWith("set pid")) {
    
        float Kp, Ki, Kd;

        int res = sscanf(command.c_str(), "set pid %f %f %f", &Kp, &Ki, &Kd);
    
        if (res == 3) {
    


            steering.setAutoSteerGains(Kp, Ki, Kd);
        
        } else {
        
            Serial.println(res);

            Serial.println("Invalid command. Usage: set pid <Kp> <Ki> <Kd>.\nIf you do not know what's wrong pay attention to spaces.\nOut program is still space sensitive.");
        
        }
    
    } else if (command.startsWith("set target")) {
    
        float target;
    
        if (sscanf(command.c_str(), "set target %f", &target) == 1) {
        
            steering.setTarget(target);
        
        } else {
            
            Serial.println("Invalid command. Usage: set target <target>.\nIf you do not know what's wrong pay attention to spaces.\nOut program is still space sensitive.");
        
        }
    
    } else if (command.startsWith("set motor")) {
    
        int PWM;
    
        if (sscanf(command.c_str(), "set motor %d", &PWM) == 1) {
            
            // Set Motor PWM.
            if ((PWM <= BLDC_MOTOR_MAX_PWM && PWM >= BLDC_MOTOR_MIN_PWM) || PWM == BLDC_MOTOR_ZERO_PWM) {

                bldc.setPWM(PWM);

            } else {

                Serial.print("set motor: PWM must be between ");
                Serial.print(BLDC_MOTOR_MIN_PWM);
                Serial.print(" and ");
                Serial.println(BLDC_MOTOR_MAX_PWM);

            }
        
        } else {
        
            Serial.println("Invalid command. Usage: set motor <PWM>.\nIf you do not know what's wrong pay attention to spaces.\nOut program is still space sensitive.");
        
        }

    } else if (command.startsWith("set servo")) {

        int PWM;

        if (sscanf(command.c_str(), "set servo %d", &PWM) == 1) {
            
            // Set Motor PWM.

            if (PWM > STEERING_SERVO_MAX_LEFT_PWM || PWM < STEERING_SERVO_MAX_RIGHT_PWM) {
            
                Serial.print("set servo: PWM must be between ");
                Serial.print(STEERING_SERVO_MAX_LEFT_PWM);
                Serial.print(" and ");
                Serial.println(STEERING_SERVO_MAX_RIGHT_PWM);
            
            } else {
            
                steering.setPWM(PWM);
            
            }
        
        } else {
        
            Serial.println("Invalid command. Usage: set motor <PWM>.\nIf you do not know what's wrong pay attention to spaces.\nOur program is still space sensitive.");
        
        }

    } else if (command.equals("set IIR")) {
    
        float alpha;

        if (sscanf(command.c_str(), "set IIR %f", alpha) == 1) {
        
            if (alpha > 1.0f || alpha < 0.0f) {
            
                Serial.println("set IIR: alpha must be between 0 and 1.");
            
            } else {
            
                steering.filter.alpha = alpha;
                steering.filter.reset();
            
            }

        } else {
        
            Serial.println("Invalid command. Usage: set IIR <alpha>.\nIf you do not know what's wrong pay attention to spaces.\nOur program is still space sensitive.");
        
        }

    } else if (command.equals("help")) {
    
        // Print help of all commands in linux terminal style.
        Serial.println("usage: <command> [options] <required_input>");
        Serial.println("Commands:");
        Serial.println("  as                          - Starts/Stops the auto steer controller");
        Serial.println("  sm                          - Starts/Stops the motor at the set PWM value");
        Serial.println("  set                         - Configure settings:");
        Serial.println("    pid <Kp:float> <Ki:float> <Kd:float>  - Sets the PID gains");
        Serial.println("    target <target:float>                 - Sets the target of the PID");
        Serial.println("    motor <PWM:int>                       - Sets the PWM for motor control");
        Serial.println("    servo <PWM:int>                       - Sets the PWM for servo control");
        Serial.println("    IIR <alpha:float>                     - Sets the alpha value for the IIR filter");
        Serial.println("  help                        - Prints this message");

    } else {
    
        Serial.println("Unknown command. Type 'help' for a list of commands.");
    
    }


}

