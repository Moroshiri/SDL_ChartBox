#include "ChartBox.hpp"
#include <math.h>
#include <cstdlib>

// ==================
// == Constructors ==
// ==================

ChartBox::ChartBox() : 
        _dataPointsCount(0), 
        _dataPoints(nullptr)
{
    setParameters(ChartParameters());
    computeAxes();
}

ChartBox::ChartBox(Rect rect, ChartParameters params) : 
        _dataPointsCount(0),
        _dataPoints(nullptr)
{
    setParameters(params);
    computeAxes();
}

// ===================
// == Deconstructor ==
// ===================

ChartBox::~ChartBox()
{
    free(_axes);
    free(_points);
}

// =================
// == Set Methodes ==
// =================

Error ChartBox::setParameters(ChartParameters cp)
{
    
    if (cp.xMax < cp.xMin || cp.yMax < cp.yMin && !cp.autoLimits)
        return Error(ERROR_CBX_PARAMETERS, "Max value less than min value");
    
    _params = cp;

    if(cp.autoLimits)
        computeLimits();

    if(cp.box.w == 0 || cp.box.h == 0)
        _params.box = CBX_DEFAULT_RECT;

    switch(cp.type)
    {
        case CBX_LINEAR: scaleMethod = ChartBoxScaling::scaleLinear; break;
        case CBX_SEMILOG_X: scaleMethod = ChartBoxScaling::scaleSemilogX; break;
        case CBX_SEMILOG_Y: scaleMethod = ChartBoxScaling::scaleSemilogY; break;
        case CBX_LOGLOG: scaleMethod = ChartBoxScaling::scaleLogLog; break;
    }

    return Error();
}

void ChartBox::setPoints(FPoint* pts, unsigned int count)
{
    if(pts != nullptr)
    {
        computeLimits(pts, count);
        _dataPoints = ChartBoxOptimizanion::dataReduction(pts, count, &_dataPointsCount, _params);
        computePoints();
    }
}

// =============================
// == Auto Configure Methodes ==
// =============================

void ChartBox::computeLimits(FPoint* data, unsigned int count)
{
    // -- Computing limits --
    float xMin = 0.0, xMax = 0.0;
    float yMin = 0.0, yMax = 0.0;
    for(int n = 0; n < count; n++)
    {
        FPoint p = data[n];
        if(p.x < xMin) xMin = p.x;
        if(p.x > xMax) xMax = p.x;
        if(p.y < yMin) yMin = p.y;
        if(p.y > yMax) yMax = p.y;
    }

    _params.xMin = xMin;
    _params.xMax = xMax;
    _params.yMin = yMin;
    _params.yMax = yMax;
}

void ChartBox::computeLimits()
{
    // -- Computing limits --
    float xMin = 0.0, xMax = 0.0;
    float yMin = 0.0, yMax = 0.0;
    for(int n = 0; n < _dataPointsCount; n++)
    {
        FPoint p = _dataPoints[n];
        if(p.x < xMin) xMin = p.x;
        if(p.x > xMax) xMax = p.x;
        if(p.y < yMin) yMin = p.y;
        if(p.y > yMax) yMax = p.y;
    }

    _params.xMin = xMin;
    _params.xMax = xMax;
    _params.yMin = yMin;
    _params.yMax = yMax;
}

void ChartBox::computePoints()
{
    float x, y;
    _points = new Point[_dataPointsCount];
    for(int n = 0; n < _dataPointsCount; n++)
    {
        _points[n] = scaleMethod(_dataPoints[n], _params);
    }
}

void ChartBox::computeAxes()
{
    // Compute axes points
    Point p1, p2, p3;
    p1 = Point(_params.box.x, _params.box.y);
    p2 = Point(p1.x, p1.y + _params.box.h);
    p3 = Point(p1.x + _params.box.w, p2.y);
    _axes = new Point[3] {p1, p2, p3};
}

// ===============
// == Rendering ==
// ===============

void ChartBox::render(SDL_Renderer* rend)
{
    renderBoard(rend);
    renderLine(rend);
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderDrawLine(rend, 10, 10, 50, 50);
    // SDL_RenderDrawLines(rend, (SDL_Point*)pts, 4);
}

void ChartBox::renderBoard(SDL_Renderer* rend)
{
    // -- Render axes --
    SDL_SetRenderDrawColor(rend, COLOR_BLACK);
    SDL_RenderDrawLines(rend, (SDL_Point*)_axes, 3);

    // -- Render grid --
    if(_params.grid)
    {
        ;
    }

    // -- Scale Marks --
    ;
}

void ChartBox::renderLine(SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, _params.lineColor);
    SDL_RenderDrawLines(rend, (SDL_Point*)_points, _dataPointsCount);
}