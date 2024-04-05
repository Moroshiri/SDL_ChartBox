#ifndef _ChartBox_hpp_
#define _ChartBox_hpp_
#include "IRenderable.hpp"
#include "Utiles.hpp"

enum ChartType
{
    CBX_LINEAR,
    CBX_SEMILOG_X,
    CBX_SEMILOG_Y,
    CBX_LOGLOG
};

struct ChartParameters
{
    ChartParameters() : 
        lineColor(COLOR_BLACK), 
        type(CBX_LINEAR), 
        xMin(0.0), xMax(0.0), 
        yMin(0.0), yMax(0.0), 
        grid(true),
        autoLimits(true)
    { }
    Color lineColor;
    ChartType type;
    float xMin, xMax;
    float yMin, yMax;
    bool grid;
    bool autoLimits;
};

const Rect CBX_DEFAULT_RECT = Rect(300, 300, 10, 10);

class ChartBox : public IRenderable
{
public:
    ChartBox();
    ChartBox(Rect, ChartParameters);
	~ChartBox();

    // Set data points for plot
    void setPoints(FPoint* pts, int count);

    // Set chart parameters
    Error setParameters(ChartParameters);

    // Get chart parameters
    ChartParameters getParameters();

    // Render chart box
    virtual void render(SDL_Renderer*);

private:
    
    void computeLimits();
    void computePoints();
    void computeAxes();

    typedef Point(*scaleTypeMethod)(FPoint, ChartBox*);
    scaleTypeMethod scaleMethod;
    static Point scaleLinear(FPoint, ChartBox*);
    static Point scaleSemilogX(FPoint, ChartBox*);
    static Point scaleSemilogY(FPoint, ChartBox*);
    static Point scaleLogLog(FPoint, ChartBox*);

    void renderBoard(SDL_Renderer*);
    void renderLine(SDL_Renderer*);

    Rect _box;
    FPoint* _dataPoints;
    int _dataPointsCount;
    ChartParameters _params;
    
    Point* _axes;
    Point* _points;
};

#endif