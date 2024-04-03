#ifndef _ChartBox_hpp_
#define _ChartBox_hpp_
#include "IRenderable.hpp"
#include "Types.hpp"
#include <vector>

class ChartBox : public IRenderable
{
public:
    ChartBox();
	~ChartBox();

    void addPoints(Point*);

    virtual void Render(SDL_Renderer*);

private:
    void renderBoard();
    void renderLine();

    Point* _points;
    int _pointsCount;
};


#endif