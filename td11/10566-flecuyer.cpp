#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// 10566 - Crossed Ladders

// Méthode : dichotomie de gros bourrin


class Droite
{
	public:
	double xa, xb, ya, yb;
	double m, p;
	bool vertical;
	Droite(double x1, double y1, double x2, double y2):
		xa(x1), xb(x2), ya(y1), yb(y2)
	{
		if(x1 == x2)
		{
			this->vertical = true;
			this->p = x1;
			this->m = 10000; // infinity
		}
		else
		{
			this->vertical = false;
			this->m = (y2 - y1) / (x2 - x1);
			this->p = y1 - m*x1;
		}
	}

	double operator()(double x)
	{
		if(this->vertical)
			return this->p;
		else
			return x*this->m + this->p;
	}

	void print()
	{
		cout << endl << "function: y="<<this->m<<"*x+"<<this->p<<endl;
	}
};

double intersection(Droite f, Droite g)
{
	return (f.p - g.p) / (g.m - f.m);
}

int main()
{
    cout << fixed << setprecision(3);
    double x, y, c;
    while(cin >> x >> y >> c)
    {
        double d1 = 0.001, d2 = y;

        while(d2-d1 > 0.00001)
        {
        	double d = (d2 + d1) / 2;
        	//cout << d1 << " " << d2 << endl;
        	double h = sqrt(x*x - d*d);
        	double l = sqrt(y*y - d*d);
        	Droite f(0,h,d,0), g(0,0,d,l);
        	if(f(intersection(f, g)) > c)
        	{ // on est pas assez loin, on augmente d
        		d1 = d;
        	}
        	else // on est trop loin, on recule
        		d2 = d;
        }

        cout << (d1+d2)/2 << endl;
    }
    return 0;
}