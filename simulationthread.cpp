#include "simulationthread.h"
#include<QtCore>
#include<iostream>
#include<memory>
#include<iostream>

SimulationThread::SimulationThread(QObject *parent)
{

}

SimulationThread::SimulationThread(QObject *parent,unsigned Size)
{
    size=Size;
}

SimulationThread::~SimulationThread()
{
    Clean();
}

void SimulationThread::Initialize()
{
    N=size*size;
    ising=new MonteCarlo(size,initialState);
    mcStep=0;
}

void SimulationThread::Clean()
{
    delete ising;
}

void SimulationThread::run()
{
    forever
    {
        if(status==0) //Initialize
        {
            Initialize();
            ising->setTemperature(T);
            status=3;
            emit updateData(mcStep,size);
        }
        else if(status==1) //Running
        {
            ising->run(algorithm);

            if(measurementOn)
            {
                E=ising->getEnergy();
                M=ising->getMagnetization();
            }
            mcStep++;
            emit updateData(mcStep,size);
        }
        else if(status==2) //Reset
        {
            Clean();
            status=0;
        }
        //3 = Do nothing
    }
}

void SimulationThread::SetStatus(unsigned Status)
{
    status=Status;
}

void SimulationThread::ChangeTemp(float temp)
{
    T=temp;
    ising->setTemperature(T);
}

void SimulationThread::ChangeSize(uint Size)
{
    size=Size;
    if(status!=10)status=2;
}

void SimulationThread::changeInitialState(uint InitialState)
{
    initialState=InitialState;
    if(status!=10)status=2;
}

void SimulationThread::changeAlgorithm(uint Algorithm)
{
    algorithm=Algorithm;
}

std::vector<spin> SimulationThread::CopySpins()
{
    mutex.lock();
        spin *s=ising->getSpins();
        std::vector<spin> v(s,s+N);
    mutex.unlock();

    return v;
}

ObsData SimulationThread::getObservables()
{
    return {E,M};
}

void SimulationThread::MeasurementOn(uint Status)
{
    measurementOn=Status;
}
