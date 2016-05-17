#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

#define INF 100000

using namespace std;

// collatz

int collatzSize(vector<int> &sizes, const int n, const int k)
{
	if(k < sizes.size() && sizes[k] > 0)
		return sizes[k];
	
	int val;
	if(k%2 == 0)
		val = 1+collatzSize(sizes, n, k/2);
	else
		val = 1+collatzSize(sizes, n, 3*k+1);
	if(k < sizes.size())
		sizes[k] = val;
	return val;
}



int main()
{
    int nn, mm;
    while(cin >> nn >> mm)
    {
        int n = min(nn, mm);
        int m = max(nn,mm);
        vector<int> sizes(m+1, -1);
        sizes[1] = 1;

        for(int i=n; i<=m; i++)
        	collatzSize(sizes, n, i);

		int maxSize(0);
        for(int j=n; j<=m; j++)
        	maxSize = max(maxSize, sizes[j]);        

        cout << nn << " " << mm << " " << maxSize << endl;
    }

    return 0;
}