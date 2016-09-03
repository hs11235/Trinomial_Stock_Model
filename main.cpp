#include "TriModel01.h"
#include "TriModel01.cpp"
#include "Proj01_Options.h"
//#include "Proj01_Options.cpp"
#include <iostream>
#include<fstream>

using namespace std;

int main()
{
    // Obligatory 'Hello World'!
    cout << "Hello World!" << endl;

    // Declaring relevant variables.
    double S0, r, q, sigma, T, N, K;
    vector<double> Greeks;

    cout << "Enter S0:  "; cin >> S0;
    cout << "Enter r:  "; cin >> r;
    cout << "Enter q:  "; cin >> q;
    cout << "Enter sigma:  "; cin >> sigma;
    cout << "Enter T:  "; cin >> T;
    cout << "Enter N:  "; cin >> N;
    cout << "Enter K:  "; cin >> K;
    cout << endl;

    // Initialising an Object of the TriModel class.
    TriModel Model(S0, r, q, sigma);

    // Setting appropriate parameters, as input by user.
    Model.Setdt(T, N);

    // Initialising an Object of Call class, an extension of EurOption.
    Call Option1;
    Option1.SetN(N);
    Option1.SetK(K);

    // Initialising an Object of Put class, an extension of EurOption.
    Put Option2;
    Option2.SetN(N);
    Option2.SetK(K);

    // Open excel documents and set up appropriate column headings.
    ofstream OptionOut;
    OptionOut.open("EurPrices.csv",std::ios::app);

    ofstream GreekOut;
    GreekOut.open("EurGreeks.csv",std::ios::app);

    OptionOut << "S0" << "," << "r" << "," << "q" << "," << "sigma" << ","
              << "T" << "," << "N" << "," << "Call Value" << ","
              << "Put Value";
    OptionOut << endl;

    GreekOut << "S0" << "," << "r" << "," << "q" << "," << "sigma" << ","
             << "T" << "," << "N" << "," << "delta; call" << ","
             << "gamma; call" << "," << "theta; call" << "," << "delta; put"
             << "," << "gamma; put" << "," << "theta; put";
    GreekOut << endl;

    // Output option and greek prices to appropriate excel files.
    OptionOut << S0 << "," << r << "," << q << "," << sigma << "," << T
              << "," << N << "," << Option1.PriceByCRR(Model, Greeks);

    GreekOut << S0 << "," << r << "," << q << "," << sigma << "," << T
             << "," << N << "," << Greeks[0] << "," << Greeks[1] << ","
             << Greeks[2];

    OptionOut << "," << Option2.PriceByCRR(Model, Greeks);

    GreekOut << "," << Greeks[0] << "," << Greeks[1] << "," << Greeks[2];

    OptionOut << endl;
    GreekOut << endl;

    // Also output to console.
    cout << "Value of Call Option: " << Option1.PriceByCRR(Model, Greeks) << endl;
    cout << "Call Option delta: " << Greeks[0] << endl;
    cout << "Call Option gamma: " << Greeks[1] << endl;
    cout << "Call Option theta: " << Greeks[2] << endl;

    cout << "Value of Put Option: " << Option2.PriceByCRR(Model, Greeks) << endl;
    cout << "Put Option delta: " << Greeks[0] << endl;
    cout << "Put Option gamma: " << Greeks[1] << endl;
    cout << "Put Option theta: " << Greeks[2] << endl;

/*
    // For Q4; a loop to compute option and greek prices from N=1,500.
    for(int i=1; i<=N; i++)
    {
        Model.Setdt(1, i);
        Option1.SetN(i);
        Option2.SetN(i);

        OptionOut << S0 << "," << r << "," << q << "," << sigma << "," << T
                  << "," << i << "," << Option1.PriceByCRR(Model, Greeks);

        GreekOut << S0 << "," << r << "," << q << "," << sigma << "," << T
                 << "," << i << "," << Greeks[0] << "," << Greeks[1] << ","
                 << Greeks[2];

        OptionOut << "," << Option2.PriceByCRR(Model, Greeks);

        GreekOut << "," << Greeks[0] << "," << Greeks[1] << "," << Greeks[2];

        OptionOut << endl;
        GreekOut << endl;
    }
*/
    return 0;
}
