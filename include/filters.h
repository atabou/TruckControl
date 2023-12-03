#ifndef FILTERS_H

    #define FILTERS_H

    struct IIRFilter {

        float alpha;
        float prev;

        /**
         * @brief Construct a new default IIR Filter object.
         */
        IIRFilter();


        /**
         * @brief Construct a new IIR Filter object with a given filter coefficient.
         * 
         * @param alpha The filter coefficient.
        */
        IIRFilter(float alpha);


        /**
         * @brief Passes a value through the filter.
         * 
         * @param curr The current value.
         * @return float The filtered value.
         * 
         * @note The filter is updated after the value is passed.
        */
        float pass(float curr);


        /**
         * @brief Resets the filter.
        */
        void reset();


    };

#endif // FILTERS_H