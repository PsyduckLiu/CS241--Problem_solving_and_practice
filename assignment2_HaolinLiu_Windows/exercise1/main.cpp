#include <iostream>
#include <cmath>
using namespace std;
class error{};

class Fraction
{
    int numerator;//分子
    int denominator;//分母
    int sign;
    public:
    Fraction(int n = 0, int d = 1);
    ~Fraction();
    void setFract(int n, int d);
    friend ostream &operator << (ostream &out, const Fraction &f);
    friend istream &operator >> (istream &in, Fraction &f);
    friend Fraction operator + (const Fraction &f1, const Fraction &f2);
    friend Fraction operator - (const Fraction &f1, const Fraction &f2);
    friend Fraction operator * (const Fraction &f1, const Fraction &f2);
    friend Fraction operator / (const Fraction &f1, const Fraction &f2);
    Fraction operator - ();
    Fraction &operator =(const Fraction &f);
    friend int operator == (const Fraction &f1, const Fraction &f2);
    void yueFen();
};

Fraction::Fraction(int n, int d)
{
    int temp = n * d;
    if (temp < 0)
    {
        sign = -1;
        numerator = abs(n);
        denominator = abs(d);
        yueFen();
    }
    else if (temp == 0)
    {
        if (n == 0&& d != 0)
        {
            sign = 1;
            numerator = 0;
            denominator = d;
        }
        else
            cout << "除数不能为零!" << endl;
    }
    else
    {
        sign = 1;
        numerator = n;
        denominator = d;
    }
}

Fraction::~Fraction()
{
}
void Fraction::setFract(int n, int d)
{
    int temp = n * d;
    if (temp < 0)
    {
        sign = -1;
        numerator = abs(n);
        denominator = abs(d);
        yueFen();
    }
    else if (temp == 0)
    {
        if (n == 0 && d != 0)
        {
            sign = 1;
            numerator = 0;
            denominator = d;
        }
        else
            cout << "除数不能为零!" << endl;
    }
    else
    {
        sign = 1;
        numerator = n;
        denominator = d;
    }
}

ostream &operator << (ostream &out, const Fraction &f)
{
    if (f.numerator == 0)
        out << 0;
    else
    {
        if (f.denominator == f.numerator)
        {
            if (f.sign > 0)
                out << 1;
            else
                out << -1;
        }
        else
        {
            if (f.denominator == 1)
            {
                if (f.sign < 0)
                    out << -f.numerator;
                else
                    out << f.numerator;
            }
            else
            {
                if (f.sign < 0)
                    out << -f.numerator<<'/'<<f.denominator;
                else
                    out << f.numerator<<'/'<<f.denominator;
            }
        }
    }
    return out;
}

istream &operator >> (istream &in, Fraction &f)
{
    int n, d=1;
    int temp;
    in >> n;
    temp = n * d;
    if (temp < 0)
    {
        f.sign = -1;
        f.numerator = abs(n);
        f.denominator = abs(d);
        f.yueFen();
    }
    else if (temp == 0)
    {
        if (n == 0 && d != 0)
        {
            f.sign = 1;
            f.numerator = 0;
            f.denominator = d;
        }
        else
            cout << "除数不能为零!" << endl;
    }
    return in;
}


Fraction operator + (const Fraction &f1, const Fraction &f2)
{
    Fraction f;
    int fz;
    if (f1.sign * f2.sign < 0)
    {
        if (f1.sign < 0)
        {
            fz = f2.numerator * f1.denominator - f1.numerator * f2.denominator;
            if (fz < 0)
            {
                f.numerator = abs(fz);
                f.sign = -1;
            }
            else
            {
                f.numerator = fz;
                f.sign = 1;
            }
        }
        else
        {
            fz = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
            if (fz < 0)
            {
                f.numerator = abs(fz);
                f.sign = -1;
            }
            else
            {
                f.numerator = fz;
                f.sign = 1;
            }
        }
    }
    else
    {
        f.numerator = f2.numerator * f1.denominator + f1.numerator * f2.denominator;
        if (f1.sign < 0)
            f.sign = -1;
        else
            f.sign = 1;
    }
    f.denominator = f1.denominator * f2.denominator;
    f.yueFen();
    return f;
}


Fraction operator - (const Fraction &f1, const Fraction &f2)
{
    Fraction f, f2_t;
    f2_t.denominator = f2.denominator;
    f2_t.numerator = f2.numerator;
    f2_t.sign = -f2.sign;
    f = f1 + f2_t;
    f.yueFen();
    return f;
}


Fraction operator * (const Fraction &f1, const Fraction &f2)
{
    Fraction f;
    f.sign = f1.sign * f2.sign;
    f.numerator = f1.numerator * f2.numerator;
    f.denominator = f1.denominator * f2.denominator;
    f.yueFen();
    return f;
}


Fraction operator / (const Fraction &f1, const Fraction &f2)
{
    Fraction f;
    int fm_t;
    f.sign = f1.sign * f2.sign;
    f.numerator = f1.numerator * f2.denominator;
    fm_t = f1.denominator * f2.numerator ;
    if (fm_t == 0)
        cout << "除数不能为零！" << endl;
    else
        f.denominator = fm_t;
    f.yueFen();
    return f;
}


Fraction Fraction::operator - ()
{
    Fraction f;
    f.denominator = denominator;
    f.numerator = numerator;
    f.sign = -sign;
    f.yueFen();
    return f;
}
int operator == (const Fraction &f1, const Fraction &f2)
{
    Fraction f;
    f = f1 - f2;
    if (f.numerator == 0)
        return 1;
    else
        return 0;
}

Fraction &Fraction::operator =(const Fraction &f)
{
    if (this == &f)
        return *this;
    this->numerator = f.numerator;
    this->denominator = f.denominator;
    this->sign = f.sign;
    return *this;
}

void Fraction::yueFen()
{
    int m, n, r;
    m = (numerator > denominator) ? numerator : denominator;
    n = (numerator < denominator) ? numerator : denominator;
    r = n;
    while (r != 0)
    {
        r = m % n;
        m = n;
        n = r;
    }
    numerator = numerator / m;
    denominator = denominator / m;
}


int main()
{
    int a[4],b[4];
    Fraction c[4],af[4],bf[4];
    int i,m=3,n,k;
try {
    cout<<"Test Input:"<<endl;
    for (i=3;i>=0;i--) cin>>a[i];
    if (cin.fail()==1) throw error();
    if (a[3]==0) throw error();
    for (i=3;i>=0;i--) af[i]=Fraction(a[i]);
    for (i=3;i>=0;i--) cin>>b[i];
    if (cin.fail()==1) throw error();
    for (i=3;i>=0;i--) {
        if (b[i]==0) continue;
        else break;
    }
    n=i;
    for (i=3;i>=0;i--) bf[i]=Fraction(b[i]);

    for (i=0;i<4;i++) c[i]=0;

while (m>=0) {
    k=n;
    if (m>=n) {
    c[m-n]=af[m]/bf[n];
    for (i=m;i>=m-n;i--) {
        af[i]=af[i]-bf[k]*c[m-n];
        k--;
    }
    }
    m--;
    if (m<n) break;
    if (m==0&&a[m]==Fraction()) break;

}

    for (i=3-n;i>=0;i--) cout<<c[i]<<' ';
    cout<<endl;
    if (m<n) {
        for (i=m;i>=0;i--) cout<<af[i]<<' ';
    }
}
catch(error) {cout<<"error";}
system("pause");

    return 0;
}
