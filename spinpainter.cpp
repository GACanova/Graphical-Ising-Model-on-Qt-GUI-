#include "spinpainter.h"

SpinPainter::SpinPainter(QPaintDevice *widget)
{
    spinUpColor=(QColor(0,0,0,255));
    spinDownColor=(QColor(255,255,255,255));
}

void SpinPainter::paint(QPainter &qp,unsigned width,unsigned height,std::vector<spin> data,uint size)
{
    qp.setBrush(spinDownColor);
    qp.drawRect(0,0,width-1,height-1);

    const double pixelSizeX=1.*(width-1)/size;
    const double pixelSizeY=1.*(height-1)/size;

    for(unsigned i=0;i<size*size;i++)
    {
        unsigned x=(i%size)*pixelSizeX;
        unsigned y=(i/size)*pixelSizeY;

        QRectF rect;

        if(data[i]==1)
        {
            rect=(QRectF(x,y,pixelSizeX,pixelSizeY));

            qp.setPen(spinUpColor);
            qp.setBrush(spinUpColor);
            qp.drawRect(rect);
        }
    }
}
