#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// 378 - Intersecting Lines


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

int main()
{
    int N;
    cin >> N;
    cout << fixed << setprecision(2) << "INTERSECTING LINES OUTPUT" << endl;
    while(N-- > 0)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Droite f(x1, y1, x2, y2);
        cin >> x1 >> y1 >> x2 >> y2;
        Droite g(x1, y1, x2, y2);

        if((f.vertical && g.vertical) || f.m == g.m) // parallel
        {
        	if(f.p == g.p)
        		cout << "LINE" << endl;
        	else
        		cout << "NONE" << endl;
        }
        else
        {
        	double x,y;
			if(f.vertical)
        	{
        		x = f.p;
        		y = g(x);
        	}
        	else if(g.vertical)
        	{
        		x = g.p;
        		y = f(x);
        	}
        	else
        	{
        		x = (f.p - g.p) / (g.m - f.m);
				y = f(x);
			}
			cout << "POINT " << x << " " << y << endl;
		}

    }
    cout << "END OF OUTPUT" << endl;
    return 0;
}