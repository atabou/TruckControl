#ifndef COMMON_H

    #define COMMON_H

    /**
     * @brief Saturates a value between a minimum and a maximum.
     * 
     * @param x The value to saturate.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return float The saturated value.
     */   
    inline float saturate(float x, float min, float max) {

        if (x > max) return max;
        if (x < min) return min;
        return x;

    }


    /**
     * @brief Maps a value from one interval to another.
     * 
     * @param x The value to map.
     * @param min The minimum value of x's interval.
     * @param max The maximum value of x's interval.
     * @param imin The minimum value of the interval to map to.
     * @param imax The maximum value of the interval to map to.
     * @return float The mapped value.
     * 
     * @note This function saturates the value x to its given interval [min, max].
    */
    inline float map_to_interval(float x, float min, float max, float imin, float imax) {

        return imin + (imax - imin) * (saturate(x, min, max) - min) / (max - min);

    }

#endif // COMMON_H