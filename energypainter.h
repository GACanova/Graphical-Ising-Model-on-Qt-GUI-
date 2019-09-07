#ifndef ENERGYPAINTER_H
#define ENERGYPAINTER_H
#include <QPainter>
#include <vector>
#include "types.h"
#include <math.h>


class EnergyPainter
{
private:
    QColor color1,color2;

public:
    explicit EnergyPainter(QPaintDevice *widget);
    void paint(QPainter &qp, unsigned width, unsigned height, std::list<ObsData> data);
    ~EnergyPainter();
};

#endif // ENERGYPAINTER_H
