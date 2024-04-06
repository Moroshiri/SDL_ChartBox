#include "ChartBoxOptimization.hpp"
#include <math.h>

FPoint* ChartBoxOptimizanion::dataReduction(FPoint* data, unsigned int count_in, unsigned int* count_out, Rect box, ChartParameters params)
{
    if(data == nullptr || count_out == nullptr || count_in == 0)
        return nullptr;

    // No reduction if box width is higher or equal to data count
    if(box.w >= count_in)
        return data;

    unsigned int count = 0;
    FPoint* out = nullptr;
    
    // -- Linear reduction --
    if(params.type == CBX_LINEAR || params.type == CBX_SEMILOG_Y)
    {
         // Reduction ratio relative to box width, rounded up
        auto ratio = (unsigned int)std::ceil(count_in / box.w);
        auto rest = count_in % ratio;

        count = count_in / ratio;
        out = new FPoint[count + (rest > 0)];

        // Averaging method
        unsigned int n = 0, shift = 0;
        do
        {
            shift = n * ratio;
            out[n] = mean(data + shift, ratio);

            n++;
        } while(n < count);

        if(rest > 0)
        {
            out[count] = mean(data + shift, rest);
            count++;
        }

        *count_out = count;
    }

    // -- Logarithmic reduction --
    else
    {
        unsigned int n = 0, nLast = 0, m = 0;
        int x = 0, xLast = 0;
        float valueRange = std::log10(params.xMax - params.xMin);
        
        if (params.reducingMethod == CDR_AVERAGE)
        {
            count = box.w;
            out = new FPoint[count];
            
            do
            {
                // -- Compute points per pixels --

                // Compute integer of next point coordinate
                x = data[n].x > 0 ? (int)std::trunc((float)box.w / valueRange * std::log10(data[n].x)) : 0;

                // If actual x is higher than last x (integer value), count shift relative to last x and average points between them
                if(x > xLast)
                {
                    auto shift = n - nLast;
                    if (shift > 1)
                        out[m] = mean(data + nLast, shift);
                    else
                        out[m] = data[n];

                    nLast = n;
                    xLast = x;
                    m++;
                }

                n++;
            } while(n < count_in);

            if(m < count-1)
            {
                auto rest = n - nLast;
                out[count-1] = mean(data + nLast, rest);
                m++;
            }
        }
        
        if (params.reducingMethod == CDR_MINMAX)
        {
            count = box.w * 1.5;
            out = new FPoint[count];

            do
            {
                x = data[n].x > 0 ? (int)std::trunc((float)box.w / valueRange * std::log10(data[n].x)) : 0;

                if(x > xLast)
                {
                    auto shift = n - nLast;
                    if (shift > 1)
                    {
                        out[m] = min(data + nLast, shift);
                        m++;
                        out[m] = max(data + nLast, shift);
                        m++;
                    }
                    else
                    {
                        out[m] = data[n];
                        m++;
                    }

                    nLast = n;
                    xLast = x;
                }

                n++;
            } while(n < count_in);

            if(m < count-2)
            {
                auto rest = n - nLast;
                out[m] = min(data + nLast, rest);
                m++;
                out[m] = max(data + nLast, rest);
                m++;
            }
        }
        
        *count_out = m;
    }
    
    return out;
}