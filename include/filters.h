#ifndef FILTERS_H

    #define FILTERS_H

    struct IIRFilter {

        float alpha;
        float prev;


        IIRFilter();


        IIRFilter(float alpha);


        float pass(float curr);


        void reset();


    };

#endif // FILTERS_H