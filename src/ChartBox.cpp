#include "ChartBox.hpp"

ChartBox::ChartBox()
{ }

ChartBox::~ChartBox()
{ }

void ChartBox::addPoints(Point* pts)
{
    if(pts != nullptr)
    {
        _pointsCount = sizeof(pts) / sizeof(pts[0]);
        _points = pts;
    }
}

void ChartBox::Render(SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(rend, 10, 10, 50, 50);
}