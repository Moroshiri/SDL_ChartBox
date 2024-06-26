#ifndef _ChartBox_hpp_
#define _ChartBox_hpp_
#include "IRenderable.hpp"

#include "chartbox/ChartBoxOptimization.hpp"
#include "chartbox/ChartBoxScaling.hpp"

const Rect CBX_DEFAULT_RECT = Rect(300, 300, 10, 10);

class ChartBox : public IRenderable
{
public:
    ChartBox();
    ChartBox(Rect, ChartParameters);
	~ChartBox();

    // Set data points for plot
    void setPoints(FPoint* pts, unsigned int count);

    // Set chart parameters
    Error setParameters(ChartParameters);

    // Get chart parameters
    ChartParameters getParameters();

    // Render chart box
    virtual void render(SDL_Renderer*);

private:
    void computeLimits(FPoint* data, unsigned int count);
    void computeLimits();
    void computePoints();
    void computeAxes();

    typedef Point(*scaleTypeMethod)(FPoint, ChartParameters);
    scaleTypeMethod scaleMethod;

    void renderBoard(SDL_Renderer*);
    void renderLine(SDL_Renderer*);

    FPoint* _dataPoints;
    unsigned int _dataPointsCount;
    ChartParameters _params;
    
    Point* _axes;
    Point* _points;
};

#endif