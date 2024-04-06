#ifndef _ChartBoxOptimizanion_hpp_
#define _ChartBoxOptimizanion_hpp_

#include "ChartBoxParameters.hpp"
#include "../Utiles.hpp"

/**
 * Class used for data optimization for needs of CharBox
*/
class ChartBoxOptimizanion
{
public:
    ChartBoxOptimizanion();
    ~ChartBoxOptimizanion();

    static FPoint* dataReduction(FPoint* data, unsigned int count_in, unsigned int* count_out, Rect box, ChartParameters params);

private:
    

};

#endif