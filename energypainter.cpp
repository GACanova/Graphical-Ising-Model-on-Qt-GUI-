#include "energypainter.h"
#include <iostream>

EnergyPainter::EnergyPainter(QPaintDevice *widget)
{
    color1 =(QColor(0,255,0,255));
    color2 = (QColor(0,180,0,120));
}

EnergyPainter::~EnergyPainter()
{

}

void EnergyPainter::paint(QPainter &qp,unsigned width,unsigned height,std::list<ObsData> data)
{
    qp.setPen(QColor(255,255,255,255));
    qp.setBrush(QColor(40,40,40,255));

    const double Width=(width-1);
    const double Height=(height-1)/2.;

    qp.drawRoundedRect(0,    0,    Width,Height,   3,3,Qt::AbsoluteSize);
    qp.drawRoundedRect(0,Height,   Width,2.*Height,3,3,Qt::AbsoluteSize);

    QPolygonF poly1,poly2;

    double x,y1,y2;
    unsigned i=0;
    unsigned size=data.size();

    for(std::list<ObsData>::iterator it=data.begin(); it!=data.end(); it++)
    {
        x=1.*i*width/size;
        y1=(Height)*(-it->energy/2.);
        y2=(Height)*(2.-it->mag);

        if(!i)
        {
            y1=Height;
            y2=2.*Height;
        }
        else if(i==size-1)
        {
            y1=Height;
            y2=2.*Height;
        }

        i++;
        poly1.append( QPoint(x,y1) );
        poly2.append( QPoint(x,y2) );
    }

    qp.setPen(color1);
    qp.setBrush(color2);

    qp.drawPolygon(poly1);
    qp.drawPolygon(poly2);

    QFont font=qp.font() ;
    font.setPointSize(16);
    qp.setFont(font);
    qp.setPen(QColor(255,255,255,255));
    qp.drawText( QPoint(50,20),"Energy");
    qp.drawText( QPoint(50,20+Height),"Magnetization");

    qp.drawText( QPoint(5,20),"0");
    qp.drawText( QPoint(5,Height),"-2");
    qp.drawText( QPoint(5,20+Height),"1");
    qp.drawText( QPoint(5,2*Height),"0");
}





