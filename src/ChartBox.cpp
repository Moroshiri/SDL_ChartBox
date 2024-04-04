#include "ChartBox.hpp"
#include <math.h>

ChartBox::ChartBox() : _dataPointsCount(0), _box(CBX_DEFAULT_RECT)
{
    _dataPoints = nullptr;

    // Compute axes points
    Point p1, p2, p3;
    p1 = Point(_box.x, _box.y);
    p2 = Point(p1.x, p1.y + _box.h);
    p3 = Point(p1.x + _box.w, p2.y);
    _axes = new Point[3] {p1, p2, p3};
}

ChartBox::~ChartBox()
{
    free(_axes);
    free(_points);
}

void ChartBox::setPoints(FPoint* pts, int count)
{
    if(pts != nullptr)
    {
        _dataPointsCount = count;
        _dataPoints = pts;
        computeParams();
        computePoints();
    }
}

void ChartBox::computeParams()
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
        FPoint p = _dataPoints[n];
        x = (float)_box.w/(_params.xMax-_params.xMin) * p.x + (float)_box.x;
        y = (float)_box.h - (float)_box.h/(_params.yMax-_params.yMin) * p.y + (float)_box.y;
        _points[n] = Point((int)x, (int)y);
    }
}

void ChartBox::setParameters(ChartParameters cp)
{
    if (cp.xMax > cp.xMin && cp.yMax > cp.yMin)
        _params = cp;
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
}

void ChartBox::renderLine(SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, _params.lineColor);
    SDL_RenderDrawLines(rend, (SDL_Point*)_points, _dataPointsCount);
}

void ChartBox::render(SDL_Renderer* rend)
{
    renderBoard(rend);
    renderLine(rend);
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // SDL_RenderDrawLine(rend, 10, 10, 50, 50);
    // SDL_RenderDrawLines(rend, (SDL_Point*)pts, 4);
}