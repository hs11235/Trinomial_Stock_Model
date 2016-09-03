#ifndef TriModel01_h
#define TriModel01_h

class TriModel
{
    private:
        double S0; // initial stock price
        double r;    // continuous compounding interest rate
        double q;  // continuous dividend yield
        double sigma;  // volatility

        double dt;   // time interval

    public:
        // constructor to initialize the data member by list
        TriModel(double S0_, double r_, double q_, double sigma_):S0(S0_),r(r_),q(q_),sigma(sigma_)
        {

        }

        // member function to work out time interval dt
        // T is the maturity of the option, N is number of time steps
        void Setdt(double T, int N);

        // calculate the risk neutral probability of going up
        double RiskNeutProb_up();

        // calculate the risk neutral probability of going down
        double RiskNeutProb_down();

        // calculate the stock price at time step n and node i
        double S(int n, int i);

        // return the risk free interest rate r
        double Getr();

        // return time interval dt
        double Getdt();

};

#endif // TRIMODEL01_H_INCLUDED
