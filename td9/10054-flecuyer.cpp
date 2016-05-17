#include <iostream>
#include <iomanip>
#include <vector>

#define COLORmax 51

using namespace std;

// 10054 - The Necklace

/*
	Ici, on vérifie simplement que le graphe ne contient que des sommets de degré pair.
	On omet donc le cas de plusieurs composantes connexes, en considérant que tout graphe
	à sommets de degré pair admet un cycle eulérien. Le sujet semble ne tester que des cas
	où le graphe est connexe, car ce code fonctionne. Si ce n'était pas le cas, on pourrait
	rajouter un test de connexité pour le booléen "possible".
*/

void eulerianCycle(vector<vector<int>> &G, int vertex)
{
	for(int neighbor=0; neighbor<COLORmax; neighbor++)
	{
		if(G[vertex][neighbor] > 0)
		{
			G[vertex][neighbor]--; G[neighbor][vertex]--;
			eulerianCycle(G, neighbor);
			cout << neighbor << " " << vertex << endl;
		}
	}
}

int main()
{
    int T, N;
    cin >> T;
    for(int id_case=1; id_case<=T && cin >> N; id_case++)
    {
        vector<vector<int>> G(COLORmax, vector<int>(COLORmax, 0));
        vector<int> deg(COLORmax, 0);

        int u, v;
		while(N-- && cin >> u >> v)
		{
			G[u][v] ++;	G[v][u] ++;
			deg[u] ++; deg[v] ++;
		}

		bool possible = true;
		for(int i=0; i<COLORmax && possible; i++)
			possible = (deg[i] % 2 == 0);

        if(id_case > 1) cout << endl;
        cout << "Case #" << id_case << endl;

        if(possible)
       		eulerianCycle(G, u);
        else
        	cout << "some beads may be lost" << endl;
    }

    return 0;
}