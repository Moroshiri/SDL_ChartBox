#include "ChartBoxScaling.hpp"
#include <math.h>

Point ChartBoxScaling::scaleLinear(FPoint p, ChartParameters params)
{
    float x, y;
    x = (float)params.box.w / (params.xMax - params.xMin) * p.x + (float)params.box.x;
    y = (float)params.box.h - (float)params.box.h / (params.yMax - params.yMin) * p.y + (float)params.box.y;
    return Point((int)x, (int)y);
}

Point ChartBoxScaling::scaleSemilogX(FPoint p, ChartParameters params)
{
    float x, y;
    x = p.x > 1 ? (float)params.box.w / std::log10(params.xMax - params.xMin) * std::log10(p.x) + (float)params.box.x : params.box.x;
    y = (float)params.box.h - (float)params.box.h / (params.yMax - params.yMin) * p.y + (float)params.box.y;
    return Point((int)x, (int)y);
}

Point ChartBoxScaling::scaleSemilogY(FPoint p, ChartParameters params)
{
    float x, y;
    x = (float)params.box.w / (params.xMax - params.xMin) * p.x + (float)params.box.x;
    y = (float)params.box.h - (float)params.box.h / std::log10(params.yMax - params.yMin) * std::log10(p.y) + (float)params.box.y;
    return Point((int)x, (int)y);
}

Point ChartBoxScaling::scaleLogLog(FPoint p, ChartParameters params)
{
    float x, y;
    x = p.x > 1 ? (float)params.box.w / std::log10(params.xMax - params.xMin) * std::log10(p.x) + (float)params.box.x : params.box.x;
    y = (float)params.box.h - (float)params.box.h / std::log10(params.yMax - params.yMin) * std::log10(p.y) + (float)params.box.y;
    return Point((int)x, (int)y);
}