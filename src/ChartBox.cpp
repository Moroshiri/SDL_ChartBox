#include "ChartBox.hpp"
#include <math.h>

// ==================
// == Constructors ==
// ==================

ChartBox::ChartBox() : 
        _dataPointsCount(0), 
        _box(CBX_DEFAULT_RECT),
        _dataPoints(nullptr)
{
    setParameters(ChartParameters());
    computeAxes();
}

ChartBox::ChartBox(Rect rect, ChartParameters params) : 
        _dataPointsCount(0), 
        _box(rect),
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
    if(cp.autoLimits)
        computeLimits();
    else if (cp.xMax < cp.xMin || cp.yMax < cp.yMin)
        return Error(ERROR_CBX_PARAMETERS, "Max value less than min value");
    
    _params = cp;

    switch(cp.type)
    {
        case CBX_LINEAR: scaleMethod = scaleLinear; break;
        case CBX_SEMILOG_X: scaleMethod = scaleSemilogX; break;
        case CBX_SEMILOG_Y: scaleMethod = scaleSemilogY; break;
        case CBX_LOGLOG: scaleMethod = scaleLogLog; break;
    }

    return Error();
}

void ChartBox::setPoints(FPoint* pts, unsigned int count)
{
    if(pts != nullptr)
    {
        _dataPoints = dataReduction(pts, count, &_dataPointsCount);
        computeLimits();
        computePoints();
    }
}

// ==================
// == Optimization ==
// ==================

FPoint* ChartBox::dataReduction(FPoint* data, unsigned int count_in, unsigned int* count_out)
{
    if(data == nullptr || count_out == nullptr || count_in == 0)
        return nullptr;

    // No reduction if both dimenstions are higher or equal to data count
    if(_box.w >= count_in && _box.w >= count_in)
        return data;

    // Reduction ratio relative to shorter edge, rounded up
    auto ratio = (unsigned int)std::ceil(std::fmin(count_in / _box.w, count_in / _box.h));
    auto rest = count_in % ratio;

    auto count = count_in / ratio;
    FPoint* out = new FPoint[count + (rest > 0)];

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
    return out;
}

// ====================
// == Scale Methodes ==
// ====================

Point ChartBox::scaleLinear(FPoint p, ChartBox* obj)
{
    float x, y;
    x = (float)obj->_box.w / (obj->_params.xMax - obj->_params.xMin) * p.x + (float)obj->_box.x;
    y = (float)obj->_box.h - (float)obj->_box.h / (obj->_params.yMax - obj->_params.yMin) * p.y + (float)obj->_box.y;
    return Point((int)x, (int)y);
}

Point ChartBox::scaleSemilogX(FPoint p, ChartBox* obj)
{
    float x, y;
    //float a = std::log10((float)obj->_params.xMax / p.x);
    x = (float)obj->_box.w / std::log10(obj->_params.xMax - obj->_params.xMin) * std::log10(p.x) + (float)obj->_box.x;
    y = (float)obj->_box.h - (float)obj->_box.h / (obj->_params.yMax - obj->_params.yMin) * p.y + (float)obj->_box.y;
    return Point((int)x, (int)y);
}

Point ChartBox::scaleSemilogY(FPoint p, ChartBox* obj)
{
    float x, y;
    x = (float)obj->_box.w / (obj->_params.xMax - obj->_params.xMin) * p.x + (float)obj->_box.x;
    y = (float)obj->_box.h - (float)obj->_box.h / std::log10(obj->_params.yMax - obj->_params.yMin) * std::log10(p.y) + (float)obj->_box.y;
    return Point((int)x, (int)y);
}

Point ChartBox::scaleLogLog(FPoint p, ChartBox* obj)
{
    float x, y;
    x = (float)obj->_box.w / std::log10(obj->_params.xMax - obj->_params.xMin) * std::log10(p.x) + (float)obj->_box.x;
    y = (float)obj->_box.h - (float)obj->_box.h / std::log10(obj->_params.yMax - obj->_params.yMin) * std::log10(p.y) + (float)obj->_box.y;
    return Point((int)x, (int)y);
}

// =============================
// == Auto Configure Methodes ==
// =============================

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
    // _points = (Point*)malloc(sizeof(Point[_dataPointsCount]));
    _points = new Point[_dataPointsCount];
    for(int n = 0; n < _dataPointsCount; n++)
    {
        _points[n] = scaleMethod(_dataPoints[n], this);
    }
}

void ChartBox::computeAxes()
{
    // Compute axes points
    Point p1, p2, p3;
    p1 = Point(_box.x, _box.y);
    p2 = Point(p1.x, p1.y + _box.h);
    p3 = Point(p1.x + _box.w, p2.y);
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