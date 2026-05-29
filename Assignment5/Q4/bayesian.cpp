#include <iostream>
using namespace std;

int main() {

    // Prior probability of disease
    double P_Disease = 0.01;

    // Conditional probabilities
    double P_Fever_given_Disease = 0.9;
    double P_Cough_given_Disease = 0.8;

    // Assuming fever and cough are observed
    double numerator =
        P_Disease *
        P_Fever_given_Disease *
        P_Cough_given_Disease;

    double denominator =
        numerator +
        ((1 - P_Disease) * 0.2 * 0.3);

    double probability = numerator / denominator;

    cout << "Probability of Disease given Fever and Cough: "
         << probability << endl;

    return 0;
}

