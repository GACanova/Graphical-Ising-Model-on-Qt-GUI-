#include "spinwindow.h"
#include "ui_spinwindow.h"
#include <unistd.h>


SpinWindow::SpinWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpinWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint);
    this->setWindowTitle("Ising Model");
    QWidget::move(0,0);

    painterObject=new SpinPainter(this);
}

SpinWindow::~SpinWindow()
{
    delete ui;
}

void SpinWindow::paintEvent(QPaintEvent *e)
{
    QPainter qp(this);
    painterObject->paint(qp,width(),height(),data,size);
}

void SpinWindow::resizeEvent(QResizeEvent *)
{
}

void SpinWindow::closeEvent(QCloseEvent *e)
{
    e->accept();
}

void SpinWindow::updateData(std::vector<spin> Data,uint Size)
{
    data=Data;
    size=Size;
}

