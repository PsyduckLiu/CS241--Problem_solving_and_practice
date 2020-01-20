#include <iostream>
#include <iomanip>

using namespace std;

double ctok (double c)            // converts Celsius to Kelvin
{
    double k=c+273.15;
    return k;
}

int main()
{
    double d;                      //declare input variable
    cout<<"Celsius:";
    cin>>d;                          //retrieve temperature to input variable
    double k=ctok(d);                // convert temperature
    cout<<"Kelvin:"<<k<<'\n';            // print out temperature
    system("pause");

    return 0;
}
