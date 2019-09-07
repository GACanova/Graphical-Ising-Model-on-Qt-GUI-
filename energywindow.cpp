#include "energywindow.h"
#include "ui_energywindow.h"

EnergyWindow::EnergyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnergyWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    this->setWindowTitle("Ising Model");
    QWidget::move(1000,400);

    painterObject=new EnergyPainter(this);

    for(unsigned i=0;i<timeSteps;i++)data.push_back({0,0});
}

EnergyWindow::~EnergyWindow()
{
    delete painterObject;
    delete ui;
}

void EnergyWindow::updateData(ObsData Data)
{
    data.pop_front();
    data.push_back(Data);
}

void EnergyWindow::paintEvent(QPaintEvent *e)
{
    QPainter qp(this);
    painterObject->paint(qp,width(),height(),data);
}

void EnergyWindow::resizeEvent(QResizeEvent *)
{
}

void EnergyWindow::closeEvent(QCloseEvent *e)
{
    emit closeWindow();
}
