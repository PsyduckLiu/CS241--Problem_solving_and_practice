#include <iostream>
#include <cmath>

using namespace std;

double result(double x)
{
    double value=10*x*x*x-8.3*x*x+2.295*x-0.21141;
    return value;
}

int main()
{
    double a,b,mid=0,ra,rmid;
    int i=0;
    a=0.28516;
    b=0.400912;

    while (fabs(a-b)>=0.00001) {
        mid=(a+b)/2;
        ra=result(a);
        rmid=result(mid);

        cout<<"x"<<i<<":"<<' '<<mid<<endl;
        i+=1;

        if (rmid==0) break;
        else {
            if (ra*rmid>0) a=mid;
            else b=mid;
        }
    }
    
    system("pause");
    return 0;
}
