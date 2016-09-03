#include "TriModel01.h"
#include<iostream>
#include<cmath>
using namespace std;

void TriModel::Setdt(double T_,int N_)
{
    // Straightforward computation of time interval.
    dt = T_/N_;
}

double TriModel::RiskNeutProb_up()
{
    // Declaring relevant variables.
    double dx;
    double pu;
    double nu;

    // Calculating intermediate values, needed to compute risk free 'up' probability.
    nu = r - q - 0.5 * pow(sigma,2);

    dx = sigma * pow(3 * dt, 0.5);

    // Calculating risk free 'up' probability.
    pu = 0.5 * ((pow(sigma,2) * dt + pow(nu,2) * pow(dt,2)) / pow(dx,2)
                + (nu * dt) / dx);

    return pu;
}

double TriModel::RiskNeutProb_down()
{
    // Declaring relevant variables.
    double dx;
    double pd;
    double nu;

    // Calculating intermediate values, needed to compute risk free 'down' probability.
    nu = r - q - 0.5 * pow(sigma, 2);

    dx = sigma * pow(3 * dt, 0.5);

    // Calculating risk free 'down' probability.
    pd = 0.5 * ((pow(sigma,2) * dt + pow(nu,2) * pow(dt,2)) / pow(dx,2)
                - (nu * dt) / dx);

    return pd;
}

double TriModel::S(int n, int i)
{
    // Declaring relevant variables.
    double S;
    double dx;

    // Calculate increment value in logarithmic trinomial tree.
    dx = sigma * pow(3 * dt, 0.5);

    // Calculate actual stock value at node (n,i).
    S = S0 * exp(i * dx);

    return S;
}

double TriModel::Getr()
{
    // Output interest rate r.
    return r;
}

double TriModel::Getdt()
{
    // Output time increment size.
    return dt;
}
