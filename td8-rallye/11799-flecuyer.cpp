#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>

using namespace std;

// 11799 - Horror Dash

int main()
{
	int T, N;
	cin >> T;
	int c = 0;
	while(++c <= T && cin >> N)
	{
		int max_val(0);
		for(int i=0; i<N; i++)
		{
			int tmp;
			cin >> tmp;
			max_val = max(max_val, tmp);
		}
		
		cout << "Case "<<c<<": "<<max_val << endl;
	}
	
	return 0;
}
	
