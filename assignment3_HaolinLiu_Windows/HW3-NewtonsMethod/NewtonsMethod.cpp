#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double x=0.343036;
    int i=0;
    cout<<"x"<<i<<":"<<' '<<x<<endl;
    i+=1;

    while (fabs(x-0.29)>0.00001) {
        x=x-(10*x*x*x-8.3*x*x+2.295*x-0.21141)/(30*x*x-16.6*x+2.295);

        cout<<"x"<<i<<":"<<' '<<x<<endl;
        i+=1;
    }
    
    system("pause");
    return 0;
}
