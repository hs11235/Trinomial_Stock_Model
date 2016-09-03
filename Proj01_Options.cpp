#include "Proj01_Options.h"
#include "TriModel01.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double EurOption::PriceByCRR(TriModel Model, vector<double>& Greeks)
{
    // Define relevant variables.
    double qu = Model.RiskNeutProb_up();
    double qd = Model.RiskNeutProb_down();
    double qn = 1.0 - qu - qd;
    int N = GetN();

    // Size the Greeks vector appropriately.
    Greeks.resize(3);

/* Note: Code in this file eliminated using '/*' or '//' is used to output an entire trinomial tree. (More information in Developer Documentation)
    ofstream OpOut;
    OpOut.open("EurPricesFull.csv",std::ios::app);
*/
    // Define vector to store Option values.
    vector<double> Price(2*N+1);

    // Set Trinomial tree values for points at t=T.
    for (int i=0; i<=2*N; i++)
    {
        Price[i] = Payoff(Model.S(N,i-N));
        //OpOut << Price[i] << ",";
    }
    //OpOut << endl;

    // Iteratively compute nodes from i=N-1...0.
    for (int i=N-1; i>=0; i--)
    {
        for(int j=0; j<=2*i; j++)
        {
            Price[j] = (qu * Price[j+2]
                        + qn * Price[j+1]
                        + qd * Price[j])
                        * exp(-Model.Getdt() * Model.Getr());
        }

        // Compute values for delta and gamma, store a relevant value for calculating theta.
        if(i==1)
        {
            Greeks[0] = (Price[2] - Price[0]) / (Model.S(1,1) - Model.S(1,-1));

            Greeks[1] = ((Price[2] - Price[1]) / (Model.S(1,1) - Model.S(1,0))) / (0.5*(Model.S(1,1) - Model.S(1,-1)));

            Greeks[2] = Price[1];
        }

        // Calculate theta.
        if(i==0)
        {
            Greeks[2] = (Greeks[2] - Price[0]) / Model.Getdt();
        }
/*
        for(int j=0; j<=2*i; j++)
        {
            OpOut << Price[j] << ",";
        }
        OpOut << endl; */
    }

    return Price[0];
}

// Payoff function for a European call option.
double Call::Payoff(double z)
{
    if (z > K) return z - K;

    return 0.0;
}

// Payoff function for a European put option.
double Put::Payoff(double z)
{
    if (z < K) return K - z;

    return 0.0;
}
