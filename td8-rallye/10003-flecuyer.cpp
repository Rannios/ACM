#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

#define MILLLE 1000000

using namespace std;

// 10003 - Cutting sticks

/*
 c(i, i) = 0
 c(i, i+1) = 0
 c(i, j) = d[j]-d[i] + min k dans ]i,j[ ( c(i,k)+c(k,j) )
 */

int prog_dyn_lol(vector<vector<int>> &ptn, vector<int> &d, int i, int j)
{
	
	if(ptn[i][j] >= 0)
		return ptn[i][j];
	
	int r(0);
	if(i < j-1)
	{
		int cout = d[j] - d[i];
		int ajout = MILLLE;
		for(int k=i+1; k<j; k++)
		{
			ajout = min(ajout,  prog_dyn_lol(ptn, d, i,k) + prog_dyn_lol(ptn, d,k,j));
		}
		r = cout+ajout;
	}
	
	ptn[i][j] = r;
	return r;
}

int main()
{
	int l;
	while(cin >> l && l > 0)
	{
		int n;
		cin >> n;
		vector<int> cuts;
		cuts.push_back(0);
		for(int i=0; i<n; i++)
		{
			int tmp; cin >> tmp;
			cuts.push_back(tmp);
		}
		cuts.push_back(l);
		
		vector<vector<int>> ptn(n+2, vector<int>(n+2, -1));		
		
		cout << "The minimum cutting is "<< prog_dyn_lol(ptn, cuts, 0, n+1) <<"." <<endl;
	}
	return 0;
}
