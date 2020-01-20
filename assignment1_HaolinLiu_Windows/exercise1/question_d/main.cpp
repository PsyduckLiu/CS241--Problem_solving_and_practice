#include <iostream>
#include <iomanip>

using namespace std;
class error {};

double ctok (double c)            // converts Celsius to Kelvin
{
    if (c<-273.15) throw error();
    else {
        double k=c+273.15;
        return k;
    }
}

int main()
{
    double d;                      //declare input variable
    cout<<"Celsius:";
    cin>>d;                       //retrieve temperature to input variable
                            
    try {
    double k=ctok(d);                // convert temperature
    cout<<"Kelvin:"<<k<<'\n';            // print out temperature
    }
    catch (error) {
        cout<<"Error reporting!"<<'\n';
    }
    
    system("pause");
    return 0;
}
