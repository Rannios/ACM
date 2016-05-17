#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

#define INF 100000

#define HEIGHT 10
#define WIDTH 100
#define UP 60
#define DOWN 20
#define CONS 30

using namespace std;

// helicoptere

/*
	Dynamic programming:

	f(i, j) = smallest usage of fuel to go from 0,0 to i,j
	f(0,0) = 0
	f(i>0, 0) = +inf
	f(i, j) = min{
				f(i,j-1)+CONS
				f(i-1,j-1)+UP (if not too low)
				f(i+1,j-1)+DOWN (if not too high)
			}
*/

typedef vector<int> vi; // vector of int
typedef vector<vi> mi; // matrix of int

int f(const mi &wind, mi &fuels, int i, int j) // i: altitude, j: distance
{
	if(fuels[i][j] >= 0)
		return fuels[i][j];

	int smallest = f(wind, fuels, i, j-1) - wind[i][j-1] + CONS;
	if(i-1 >= 0)
		smallest = min(smallest, f(wind, fuels, i-1, j-1) - wind[i-1][j-1] + UP);

	if(i+1 < HEIGHT)
		smallest = min(smallest, f(wind, fuels, i+1, j-1) - wind[i+1][j-1] + DOWN);

	fuels[i][j] = smallest;
	return smallest;
}


int main()
{
    int N;	cin >> N;
    while(N--)
    {
        int X;	cin >> X;
        int D = X/WIDTH;

        mi wind(HEIGHT, vi(D));
        for(int i=HEIGHT-1; i>=0; i--)
    	for(int j=0; j<D; j++)
    	{
    		int w; cin >> w;
    		wind[i][j] = w;
    	}

        mi fuels(HEIGHT, vi(D, -1));
        fuels[0][0] = 0;
        for(int i=1; i<HEIGHT; i++)
        	fuels[i][0] = INF;

        int result = min( f(wind, fuels, 0, D-1)-wind[0][D-1]+CONS, f(wind, fuels, 1, D-1)-wind[1][D-1]+DOWN);
        cout << result << endl;
        if(N) cout << endl;
    }

    return 0;
}