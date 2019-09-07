#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ising Model");

    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    QWidget::move(1000,0);

    //QFile testIt("../images/ising.png");
    QFile testIt("~/ising.png");
    qDebug() << "Are you loading?: " << testIt.exists();
    QPixmap pix("../images/ising.png");

    simulationThread=new SimulationThread(this);

    qRegisterMetaType<spin>();
    connect(simulationThread,SIGNAL(updateData(unsigned,unsigned)),this,SLOT(NewDataReceived(unsigned,unsigned)));
    connect(this,SIGNAL(startSignal(unsigned)),simulationThread,SLOT(SetStatus(unsigned)));
    connect(this,SIGNAL(tempSignal(float)),simulationThread,SLOT(ChangeTemp(float)));
    connect(this,SIGNAL(sizeSignal(uint)),simulationThread,SLOT(ChangeSize(uint)));
    connect(this,SIGNAL(initStateSignal(uint)),simulationThread,SLOT(changeInitialState(uint)));
    connect(this,SIGNAL(algorithmSignal(uint)),simulationThread,SLOT(changeAlgorithm(uint)));
    connect(this,SIGNAL(measurementSignal(uint)),simulationThread,SLOT(MeasurementOn(uint)));

    spinWindow=new SpinWindow(this);
    spinWindow->show();

    Initialize();
    simulationThread->start();
}

MainWindow::~MainWindow()
{
    delete spinWindow;
    delete simulationThread;
    delete ui;
}

void MainWindow::Initialize()
{
    size=512;
    T=0.;
    sizeSignal(size);
    initStateSignal(1);
    startSignal(0);
    ui->radioButton->setChecked(true);

    ui->labelTemperature->setText("T="+QString::number(T));
    ui->labelSize->setText("L="+QString::number(size));
}

void MainWindow::NewDataReceived(unsigned mcStep,unsigned Size)
{
    ui->label->setText("MC Step="+QString::number(mcStep));

    spinWindow->updateData(simulationThread->CopySpins(),Size);
    spinWindow->update();

    if(energyWindowOn)
    {
        energyWindow->updateData(simulationThread->getObservables());
        energyWindow->show();
        energyWindow->update();
    }
}

void MainWindow::on_pushButtonTemperature_clicked()
{
    float tmp=ui->editTemperature->toPlainText().toFloat(NULL);

    if(tmp<0.)
    {
        tmp=0.;
    }

    T=tmp;
    tempSignal(T);

    ui->labelTemperature->setText("T="+QString::number(T));
}

void MainWindow::on_pushButtonSize_clicked()
{
    float tmp=ui->editSize->toPlainText().toFloat(NULL);

    if(tmp<16.)
    {
        tmp=16.;
    }

    size=static_cast<uint>(tmp);
    status=0;

    sizeSignal(size);
    ui->labelSize->setText("L="+QString::number(size));
}

void MainWindow::on_pushButtonStart_clicked()
{
    startSignal(1);
    status=1;
}

void MainWindow::on_pushButton_clicked()
{
    startSignal(3);
}

void MainWindow::on_radioButton_clicked()
{
    initStateSignal(1);
}

void MainWindow::on_radioButton_2_clicked()
{
    initStateSignal(0);
}

void MainWindow::on_pushButtonSG_clicked()
{
    algorithmSignal(0);
}

void MainWindow::on_pushButtonWolff_clicked()
{
    algorithmSignal(1);
}

void MainWindow::on_pushButtonEnergy_clicked()
{
    if(!energyWindowOn)
    {
        energyWindow=new EnergyWindow(this);
        energyWindowOn=true;
        connect(energyWindow,SIGNAL(closeWindow()),this,SLOT(closeEnergyWindow()));
        measurementSignal(1);
    }
}

void MainWindow::on_pushButtonReset_clicked()
{
    sizeSignal(size);
}

void MainWindow::closeEnergyWindow()
{
    delete energyWindow;
    energyWindowOn=false;
    measurementSignal(0);
}

void MainWindow::on_actionSave_file_triggered()
{
    startSignal(3);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Data (*.dat *.txt)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName=dialog.getSaveFileName(this, tr("Save File"));
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    std::vector<spin> v(simulationThread->CopySpins());

    for(auto &i:v)
    {
        out << i << "\n";
    }

    file.close();
}
