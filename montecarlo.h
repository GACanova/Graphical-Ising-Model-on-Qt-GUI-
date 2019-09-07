#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "types.h"

#ifdef DEBUG
#define SEED 123456
#else
#define SEED time(NULL)         /* Seed of the random number generator */
#endif

class MonteCarlo
{
private:
    uint **neighbors,L{32},N,algorithm{1},initialState{1};
    double T{0.},Psg[3],Pw;
    spin *s{nullptr},E{0},M{0};

private:
    void Initialize();
    void SquareLattice();
    void SingleFlip();
    void WolffAlgorithm();
    void InitialState();
    spin Energy();
    spin Magnetization();

public:
    MonteCarlo();
    MonteCarlo(uint size,uint InitialState);
    ~MonteCarlo();
    double getEnergy();
    double getMagnetization();
    void setTemperature(double temp);
    spin* getSpins();
    void run(int Algorithm);
};

#endif // MONTECARLO_H
