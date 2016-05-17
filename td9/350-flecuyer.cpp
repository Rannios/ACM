#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// 350 - Pseudo-Random Numbers


int main()
{
	int id_case(0), Z, I, M, L;
	while(cin >> Z >> I >> M >> L && M > 0)
	{
		vector<int> generated(M, -1);
		Z = Z%M;	I = I%M;	L = L%M;

		int length = 0;
		while(generated[L] == -1)
		{
			generated[L] = length++;
			L = (Z*L + I) % M;
		}
		
		cout << "Case " << ++id_case << ": " << length-generated[L] << endl;
	}

	return 0;
}