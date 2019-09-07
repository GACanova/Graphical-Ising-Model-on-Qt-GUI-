#ifndef SPINPAINTER_H
#define SPINPAINTER_H
#include <QPainter>
#include <vector>
#include "types.h"
#include <math.h>

class SpinPainter
{
private:
    QColor spinUpColor,spinDownColor;

public:
    explicit SpinPainter(QPaintDevice *widget);
    ~SpinPainter();
    void paint(QPainter &qp, unsigned width, unsigned height, std::vector<spin> data, uint size);
};

#endif // SPINPAINTER_H
