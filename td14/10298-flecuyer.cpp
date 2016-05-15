#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// 10298 - Power Strings


bool valid(const string &s, int n)
{
	if(s.size() % n)
		return false;

	int a = s.size() / n;
	for(int i=0; i<a; i++) // for each char of the subword
	for(int j=1; j<n; j++) // for each factor
		if(s[j*a + i] != s[i])
			return false;
	return true;
}

int main()
{
	string s;
	while(getline(cin, s) && s != ".")
	{
		int n = s.size();
		while(n && !valid(s, n))
			n--;
		cout << n << endl;
	}
	return 0;
}