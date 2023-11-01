#ifndef BLDC_H

    #define BLDC_H

    #include <Servo.h>

    #define BLDC_MOTOR_PWM_PIN 10
    #define BLDC_MOTOR_ZERO_PWM 900
    #define BLDC_MOTOR_MAX_PWM 2000
    #define BLDC_MOTOR_MIN_PWM 1000

    /**
     * @brief Class that implements a BLDC motor.
    */
    struct BldcMotor {

        uint8_t pin;
        int pwm;
        bool  enabled;
        bool  changed;
        Servo bldc;

        BldcMotor();

        /**
         * @brief Construct a new Bldc Motor object.
         * 
         * @param pin The PWM pin the motor is connected to.
        */
        BldcMotor(uint8_t pin);


        /**
         * @brief Starts the motor.
        */
        void start();


        /**
         * @brief Stops the motor.
        */
        void stop();


        /**
         * @brief Updates the motor.
         * 
         * @note The motor is updated if and only if the motor is enabled and the PWM value has changed.
        */
        void run();


        /**
         * @brief Sets the PWM value of the motor.
         * 
         * @param pwm The PWM value.
         * 
         * @note The PWM value must be between BLDC_MOTOR_MIN_PWM and BLDC_MOTOR_MAX_PWM.
        */
        void setPWM(int pwm);

    };

#endif // BLDC_H