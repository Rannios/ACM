#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <list>
#include <cmath>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;

// 10282 - Babelfish

int main()
{
	string line;
	map<string, string> dico;

	while(getline(cin, line) && line != "")
	{
		istringstream l(line);
		string en, fr;
		l >> en >> fr;
		
		dico[fr] = en;
	}
	
	while(getline(cin, line))
	{
		if(dico[line].length() > 0)
			cout << dico[line] << endl;
		else
			cout << "eh" << endl;
	}

	return 0;
}
