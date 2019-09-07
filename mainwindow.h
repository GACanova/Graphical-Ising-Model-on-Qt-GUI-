#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulationthread.h"
#include "simulationthread.h"
#include "spinwindow.h"
#include "types.h"
#include <vector>
#include <string>
#include <math.h>
#include "energywindow.h"
#include <QFileDialog>
#include <fstream>
#include <QTextStream>
#include <QFile>

//Q_DECLARE_METATYPE(spin)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    SpinWindow *spinWindow;
    EnergyWindow *energyWindow;
    uint size,status;
    spin *spins;
    float T;
    bool energyWindowOn{false};

private:
    void SetDefaultParameters();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    SimulationThread *simulationThread;
    void Initialize();

private slots:
    void on_pushButtonTemperature_clicked();
    void on_pushButtonSize_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButton_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButtonSG_clicked();
    void on_pushButtonWolff_clicked();

    void on_pushButtonEnergy_clicked();

    void on_pushButtonReset_clicked();

    void on_actionSave_file_triggered();

public slots:
    void NewDataReceived(unsigned mcStep,unsigned Size);
    void closeEnergyWindow();

signals:
    void startSignal(unsigned);
    void tempSignal(float);
    void sizeSignal(uint);
    void initStateSignal(uint);
    void algorithmSignal(uint);
    void measurementSignal(uint);
};

#endif // MAINWINDOW_H
