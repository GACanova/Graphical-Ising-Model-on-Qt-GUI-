#include "spinswindow.h"
#include "ui_spinswindow.h"

SpinsWindow::SpinsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpinsWindow)
{
    ui->setupUi(this);
}

SpinsWindow::~SpinsWindow()
{
    delete ui;
}
