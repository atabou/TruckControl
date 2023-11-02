#ifndef STEERINGSERVO_H

    #define STEERINGSERVO_H

    #include "powersniffer.h"
    #include "filters.h"
    #include "pidcontroller.h"
    #include <Servo.h>

    #define STEERING_SERVO_PWM_PIN 9
    #define STEERING_SERVO_MAX_DEG 25.0f
    #define STEERING_SERVO_MAX_RIGHT_PWM 1000
    #define STEERING_SERVO_MAX_LEFT_PWM 2000
    #define STEERING_SERVO_CENTERED_PWM 1500
    #define POWER_SNIFFING_LEFT_COIL_PIN A5
    #define POWER_SNIFFING_RIGHT_COIL_PIN A4
    #define POWER_SNIFFING_CONTROL_SAMPLE_TIME_MS 20
    #define FILTER_ALPHA 1.0f

    /**
     * @brief Class that implements a steering servo.
    */
    struct SteeringServo {

        uint8_t pin;
        int pwm;
        float target;
        Servo servo;
        PowerSniffer ps;
        PidController pid;
        IIRFilter filter;
        bool autoSteerEnabled;

        SteeringServo() {}

        /**
         * @brief Construct a new Steering Servo object.
         * 
         * @param pin The PWM pin.
         * @param target The target angle in degrees.
         * @param Kp The proportional gain.
         * @param Ki The integral gain.
         * @param Kd The derivative gain.
         * @param dt The sampling time.
         * 
         * @note The sampling time is in milliseconds.
         * @note The sampling time must be greater than 0.
         * @note The target angle must be between -STEERING_SERVO_MAX_DEG and STEERING_SERVO_MAX_DEG.
        */
        SteeringServo(uint8_t pin, float target, float Kp, float Ki, float Kd, float dt);

        void setPWM(int pwm);


        /**
         * @brief Updates the steering servo.
         * 
         * @param curr The current angle in degrees.
        */
        void run();


        /**
         * @brief Starts the PID controller.
        */
        void enableAutoSteer();


        /**
         * @brief Sets the PID gains of the auto steer controller.
         * 
         * @param Kp The proportional gain.
         * @param Ki The integral gain.
         * @param Kd The derivative gain.
         * 
         * @note The controller is reset after the gains are set.
        */
        void setAutoSteerGains(float Kp, float Ki, float Kd);


        /**
         * @brief Sets the target angle.
         * 
         * @param target The target angle in degrees.
         * 
         * @note The target angle must be between -STEERING_SERVO_MAX_DEG and STEERING_SERVO_MAX_DEG.
        */
        void setTarget(float target);


        /**
         * @brief Disables the auto steer controller.
        */
        void disableAutoSteer();


    };

#endif // STEERINGSERVO_H