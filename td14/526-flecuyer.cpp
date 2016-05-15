#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <tuple>

#define INF 1000000

using namespace std;

// 526 - String Distance and Transform Process


/* Dynamic programming:
	The distance d(i,j) between the i first letters of u and the j first of v is such that :
	- d(0,j)=j
	- d(i,0)=i
	- d(i,j)=min {
			1 + d(i-1,j)
			1 + d(i,j-1)
			d(i-1,j-1) + (u[i] != v[j])
		}
*/
typedef pair<int,int> pii;
typedef vector<vector<pii>> matrix;

pii d(const string &u, const string &v, matrix &m, int i, int j, bool speak, int &compt)
{
	if(i < 0 || j < 0) return make_pair(INF, 0);
	if(true && !speak && m[i][j].first >= 0)
		return m[i][j];

	if(i == 0 && j == 0) return make_pair(0, 0);

	bool neq = (u[i-1] != v[j-1]);
	int del = d(u, v, m, i-1, j, false, compt).first + 1;
	int ins = d(u, v, m, i, j-1, false, compt).first + 1;
	int rep = d(u, v, m, i-1, j-1, false, compt).first + neq;
	
	int offset = 0;
	if(del <= min(ins, rep))
	{
		if(speak)
		{
			offset = d(u, v, m, i-1, j, true, compt).second + 1;
			cout << compt++ << " " << "Delete " << i-offset+1 << endl;
		}
		m[i][j] = make_pair(del, offset);
	}
	else if(ins <= min(del, rep))
	{
		if(speak)
		{
			offset = d(u, v, m, i, j-1, true, compt).second - 1;
			cout << compt++ << " " << "Insert " << i-offset << "," << v[j-1] << endl;
		}
		m[i][j] = make_pair(ins, offset);
	}
	else // if(rep <= min(del, ins))
	{
		if(speak)
		{
			offset = d(u, v, m, i-1, j-1, true, compt).second;
			if(neq)
				cout << compt++ << " " << "Replace " << i-offset << "," << v[j-1] << endl;
		}
		m[i][j] = make_pair(rep, offset);
	}

	return m[i][j];
}

int main()
{
	bool first = true;
	string u, v;
	while(getline(cin, u) && getline(cin, v) && (u.size() || v.size()))
	{
		if(first)
			first = false;
		else
			cout << endl;
		matrix m(81, vector<pii>(81, make_pair(-1,0)));
		int compt = 1;
		cout << d(u, v, m, u.size(), v.size(), false, compt).first << endl; // print the distance
		d(u, v, m, u.size(), v.size(), true, compt); // print the steps
	}

	return 0;
}
