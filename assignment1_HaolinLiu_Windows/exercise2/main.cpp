#include <iostream>
#include "solve.h"
#include <cmath>

using namespace std;

class noroot {};
class notequation {};
class notdouble{};

int main()
{
    double a,b,c;
    try {
        cin>>a>>b>>c;
        if (cin.fail()==1) throw notdouble();

        else {
            double dlt=solve(a,b,c);
            double x1=(-b+sqrt(dlt))/(2*a);
            double x2=(-b-sqrt(dlt))/(2*a);
            cout<<x1<<' '<<x2;
        }
    }

    catch (notdouble) {cout<<"Illegal inputs!";}
    catch (noroot) {cout<<"b2-4ac is less than zero!";}
    catch (notequation) {cout<<"Illegal inputs!";}
    system("pause");
    return 0;

}
