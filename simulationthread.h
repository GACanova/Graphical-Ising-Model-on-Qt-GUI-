#ifndef SIMULATIONTHREAD_H
#define SIMULATIONTHREAD_H

#include <QObject>
#include <QThread>
#include "montecarlo.h"
#include "types.h"
#include <vector>
#include <QMutex>
#include <queue>

//Q_DECLARE_METATYPE(spin)

class SimulationThread : public QThread
{
    Q_OBJECT
private:
    unsigned size{40},N,mcStep{0},status{10},initialState{1},algorithm{0},measurementOn{0};
    double T{0.},E{0},M{0};
    int *spins;
    MonteCarlo *ising;
    QMutex mutex;

public:
    explicit SimulationThread(QObject *parent=0);
    SimulationThread(QObject *parent,unsigned size);
    void Initialize();
    void Clean();
    spin *getSpins(const spin *S);
    std::vector<spin> CopySpins();
    ObsData getObservables();

    ~SimulationThread();
    void run();
    bool stop;

signals:
    void updateData(unsigned,unsigned);

public slots:
    void SetStatus(unsigned Status);
    void ChangeTemp(float temp);
    void ChangeSize(uint Size);
    void changeInitialState(uint InitialState);
    void changeAlgorithm(uint Algorithm);
    void MeasurementOn(uint Status);
};

#endif // SIMULATIONTHREAD_H
