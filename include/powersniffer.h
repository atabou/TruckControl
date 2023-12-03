#ifndef POWERSNIFFER_H

    #define POWERSNIFFER_H

    struct PowerSniffer {

        int leftPin;
        int rightPin;
        int bias;


        PowerSniffer() {}


        /**
         * @brief Construct a new Power Sniffer object.
         * 
         * @param leftPin The pin of the left coil.
         * @param rightPin The pin of the right coil.
         * 
         * @note The bias is set to 0.25 by default.
        */
        PowerSniffer(int leftPin, int rightPin);


        /**
         * @brief Get the current reading of the power sniffer.
         * 
         * @return float The current reading of the power sniffer.
        */
        float getReading();


        /**
         * @brief Set the bias of the power sniffer.
         * 
         * @param bias The bias of the power sniffer.
        */
        void setBias(float bias);

        ~PowerSniffer() {}

    };


#endif // POWERSNIFFER_H