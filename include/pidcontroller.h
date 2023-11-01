#ifndef PIDCONTROLLER_H

    #define PIDCONTROLLER_H

    #include "powersniffer.h"

    /**
     * @brief Class that implements a PID controller.
    */
    struct PidController {

        float Kp;
        float Kd;
        float Ki;
        float dt;

        float derr;
        float ierr;

        PidController();


        /**
         * @brief Construct a new Pid Controller object.
         * 
         * @param Kp The proportional gain.
         * @param Ki The integral gain.
         * @param Kd The derivative gain.
         * @param dt The sampling time.
         * 
         * @note The sampling time is in milliseconds.
         * @note The sampling time must be greater than 0.
        */
        PidController(float Kp, float Ki, float Kd, float dt);


        /**
         * @brief Updates the controller.
         * 
         * @param target The target value.
         * @param curr The current value.
         * 
         * @return float The response of the controller.
        */
        float update(float target, float curr);


        /**
         * @brief Resets the controller to its initial state.
        */
        void reset();


    };


#endif // PIDCONTROLLER_H