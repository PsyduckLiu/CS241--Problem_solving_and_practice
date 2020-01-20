#include<iostream>
#include<iomanip>
#include<cstring>

using namespace std;

class error{};

class NewtonInterpolation {
public:
      double x[7]={0.1,0.4,1.0,1.8,2.9,3.2,3.8};
      double y[7]={4.2,3.8,2.5,2.0,-2.0,0.0,-0.3};
      double matrix[7][7];

void DividedDifferenceTable()
{
    for(int i=0;i<7;i++) matrix[i][0]=y[i];
    for(int i=1;i<7;i++) {
        for(int j=i;j<7;j++)
        {
            matrix[j][i] = (matrix[j-1][i-1]-matrix[j][i-1])/(x[j-i]-x[j]);
        }
    }
    cout<<"Divided Difference Table:"<<endl;
    for(int i=0;i<7;i++) {
        for(int j=0;j<i+1;j++) {
            cout<<setw(10)<<matrix[i][j]<<' ';
    }
    cout << endl;
    }
}

double ApproximateValue(double newx)
{
    double data=newx,ans,t;
    ans = matrix[0][0];
    for(int i=1;i<7;i++) {
        t = matrix[i][i];
        for(int j=i-1;j>=0;j--)
            t*=(data-x[j]);
        ans+=t;
    }
return ans;
}

};

int main()
{
    double xnew;
    NewtonInterpolation a;
    a.DividedDifferenceTable();

  try {
    cout<<"Test Input:";
    cin>>xnew;
    if (cin.fail()==1) throw error();
    cout<<a.ApproximateValue(xnew);
  }

catch(error) {cout<<"error";}
system("pause");
    return 0;
}

