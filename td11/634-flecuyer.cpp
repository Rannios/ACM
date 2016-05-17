#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>

using namespace std;

// 634 - Polygon

// Méthode : compter le nombre d'intersection avec le polygone

int main()
{
    int N;
    cout << fixed << setprecision(3);
    while(cin >> N && N > 0)
    {
        vector<pair<int,int>> pts(N);
        int a,b; 
        for(int i=0; i<N; i++)
        {
        	cin >> a >> b;
        	pts[i] = make_pair(a, b);
        }

        cin >> a >> b;

        int nb_croismt(0);
        for(int i=0; i<N; i++)
        {
			int x1 = pts[i].first,  x2 = pts[(i+1)%N].first;
			int y1 = pts[i].second, y2 = pts[(i+1)%N].second;
        	
        	if(x1 == x2 && x1 < a) // segment vertical à gauche de P
        	{
        		if((y1 <= b && y2 >= b) || (y2 <= b && y1 >= b))
        			nb_croismt ++;
        	}
        }

        cout << (nb_croismt%2 ? "T":"F") << endl;
    }
    return 0;
}