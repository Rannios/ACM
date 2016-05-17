#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// 109 - SCUD Busters


class Vecteur
{
public:
	double x,y;
	Vecteur(double x, double y): x(x), y(y) {}
	Vecteur(): x(-1), y(-1) {}

	Vecteur operator-(const Vecteur B) const { return Vecteur(x - B.x, y - B.y); } 			// vecteur BA
	double 	operator^(const Vecteur B) const { return x * B.y - y * B.x; } 					// produit vectoriel
	double 	operator*(const Vecteur B) const { return x * B.x + y * B.y; } 					// produit scalaire
	bool   	operator<(const Vecteur B) const { return (x < B.x) || (x == B.x && y < B.y); } // ordre lexicographique
	bool   operator<=(const Vecteur B) const { return (*this < B) || (*this == B); } 		// ordre large
	bool   operator==(const Vecteur B) const { return (x == B.x && y == B.y); }				// égalité
};


class Kingdom
{
public:
	bool on;
	vector<Vecteur> buildings;
	Kingdom(const int N): N(N), surf(-1), on(true) {}

	double blackoutArea(const double x, const double y) // area shut down by (x,y)-missile
	{
		if(!on || !inside(Vecteur(x, y))) return 0;
		on = false;
		return surface();
	}

private:
	int N;
	double surf;
	vector<Vecteur> convexHull;
	vector<Vecteur> convex() // buildings of the convex hull
	{
		if(convexHull.size() == 0)	computeConvexHull();
		return convexHull;
	}
	Vecteur convex(const int i) { return convex()[i]; }

	double surface() // total surface of the convex hull
	{
		if(surf < 0 && !(surf = 0))
			for(int i=1; i<convex().size(); i++)
				surf += (convex(i-1) ^ convex(i)) / 2;
		return surf;
	}

	bool inside(const Vecteur &C) // C belongs to this kingdom ?
	{
		bool in = true;
		for(int i=1; in && i<convex().size(); i++)
			in = ( ((convex(i)-convex(i-1)) ^ (C-convex(i-1))) > 0 );
		return in;
	}
	
	void computeConvexHull() // monotone chain algorithm
	{	 
		sort(buildings.begin(), buildings.end());
		vector<Vecteur> hull;
		for(int i=0; i<N;)	computeConvexHullAUX(buildings[i++], hull, 1); // lower hull
		for(int i=N, lowerSize=hull.size(); i;)	computeConvexHullAUX(buildings[--i], hull, lowerSize); // upper hull
		convexHull = hull;
	}
	void computeConvexHullAUX(const Vecteur &C, vector<Vecteur> &hull, const int mini)
	{
		while(hull.size() > mini)
		{
			Vecteur B = hull.back(); hull.pop_back(); Vecteur A = hull.back();
			if( ((B-A)^(C-A)) > 0 ) { hull.push_back(B); break; }
		}
		hull.push_back(C);
	}
};

int main()
{
    vector<Kingdom> kingdoms;
    int N, x, y;
    while(cin >> N && N > 0) // kingdoms
    {
        Kingdom K(N);
        while(N-- && cin >> x >> y)
        	K.buildings.push_back(Vecteur(x, y));
       	kingdoms.push_back(K);
    }
    
    double surface = 0;
    while(cin >> x >> y) // missiles
    {
    	for(int k=0; k<kingdoms.size(); k++)
    		surface += kingdoms[k].blackoutArea(x, y);
    }

    cout << fixed << setprecision(2) << surface << endl;
    return 0;
}