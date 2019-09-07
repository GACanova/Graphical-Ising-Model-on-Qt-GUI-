#include "montecarlo.h"
#include "randomGenerator.h"
#include <iostream>

MonteCarlo::MonteCarlo()
{
    Initialize();
}

MonteCarlo::MonteCarlo(uint size,uint InitialState) : L(size) , initialState(InitialState)
{
    Initialize();
}

MonteCarlo::~MonteCarlo()
{
    for(uint i=0;i<N;i++)delete[] neighbors[i];
    delete[] neighbors;
    delete[] s;
}

void MonteCarlo::Initialize()
{
    N=L*L;
    s=new spin[N];
    neighbors=new uint*[N];
    for(uint i=0;i<N;i++)neighbors[i]=new uint[4];

    initRandom((long unsigned)SEED);
    SquareLattice();
    InitialState();
    M=Magnetization();
    E=Energy();
}
void MonteCarlo::InitialState()
{
    for(uint i=0;i<N;i++)
    {
        if(initialState)
        {
            s[i]=2*(int)(2.*RAND)-1;
        }
        else
        {
            s[i]=1;
        }
    }
}

void MonteCarlo::run(int Algorithm)
{
    if(!Algorithm)
    {
        SingleFlip();
    }
    else
    {
        WolffAlgorithm();
    }
}

void MonteCarlo::setTemperature(double temp)
{
    T=temp;
    Psg[0]=0.;
    Psg[1]=exp(-4./T);
    Psg[2]=exp(-8./T);

    Pw=1.-exp(-2./T);
}

void MonteCarlo::SingleFlip()
{
        for(uint n=0;n<N;n++)
        {
                const uint i=(int)(N*RAND);
                spin Sj=0;

                for(uint k=0;k<4;k++)
                {
                        Sj+=s[neighbors[i][k]];
                }

                const spin dE=2*s[i]*Sj;

                if(dE<=0)
                {
                        s[i]*=-1;
                        E+=dE;
                        M+=2*s[i];
                }
                else if(RAND<Psg[dE>>2])
                {
                        s[i]*=-1;
                        E+=dE;
                        M+=2*s[i];
                }
        }
}

void MonteCarlo::WolffAlgorithm()
{
        uint *added=new uint[N];
        uint *list =new uint[N];

        for(uint i=0;i<N;i++)
        {
                added[i]=0;
                list[i]=N;
        }

        uint i=(int)(N*RAND);
        s[i]*=-1;
        added[i]=1;
        uint l=0,n=0;

        while(i!=N)
        {
                for(uint k=0;k<4;k++)
                {
                        const uint j=neighbors[i][k];

                        if(!added[j])
                        {
                                if(s[j]==-s[i])
                                {
                                        if(RAND<Pw)
                                        {
                                                s[j]*=-1;
                                                list[l]=j;
                                                l++;
                                                added[j]=1;
                                        }
                                }
                        }
                }

                i=list[n];
                n++;
        }
        delete[] added;
        delete[] list;
}

void MonteCarlo::SquareLattice()
{
        for(uint i=0;i<N;i++)
        {
                uint x=i%L;
                uint y=i/L;

                neighbors[i][0]=(x+1)%L + y*L;      //East
                neighbors[i][1]=(x-1+L)%L + y*L;    //West
                neighbors[i][2]=x + ((y-1+L)%L)*L;  //North
                neighbors[i][3]=x + ((y+1+L)%L)*L;  //South
       }
}

spin MonteCarlo::Energy()
{
        spin energy=0;

        for(uint i=0;i<N;i++)
        {
                for(uint j=0;j<4;j++)
                {
                        energy+=-s[i]*s[neighbors[i][j]];
                }
        }
        return energy/2;
}

double MonteCarlo::getEnergy()
{
    if(algorithm)
    {
        E=Energy();
    }

    return 1.*E/N;
}

double MonteCarlo::getMagnetization()
{
    if(algorithm)
    {
        M=Magnetization();
    }

    return 1.*abs(M)/N;
}

spin MonteCarlo::Magnetization()
{
        spin mag=0;

        for(uint i=0;i<N;i++)
        {
                mag+=s[i];

        }
        return mag;
}

spin* MonteCarlo::getSpins()
{
    return s;
}






