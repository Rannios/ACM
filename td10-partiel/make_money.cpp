#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;



int main() {
	int n;
	while (cin >> n) {
		//cerr << "ca plante la ?\n";
		vector< vector<double> > aretes(n, vector<double> (n));
		vector< vector<double> > poids(n, vector<double> (n));
		vector< vector<int> > antecedent(n, vector<int> (n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					aretes[i][i] = 1;
					poids[i][i]  = 1;
					antecedent[i][i] = -1;
				}
				else {
					double taux;
					cin >> taux;
					aretes[i][j] = taux;
					poids[i][j]  = taux;
					antecedent[i][j] = i;
					//cerr << i << " " << j << " " << taux << endl;
				}
			}
		}


		int k = 0, i = 0, j = 0;

		bool b = true;
		int length = -1, depart = -1;
		int a = 0;
		while (a < n && b) {
			k = 0;
			//cerr << "a : " << a << " " << k << " " << i << " " << j << endl;
			while (k < n && b) {
				i = 0;
				//cerr << "k : " << a << " " << k << " " << i << " " << j << endl;
				while (i < n && b) {
					j = 0;
					//cerr << "i : " << a << " " << k << " " << i << " " << j << endl;
					while (j < n && b) {
						//cerr << "j : " << a << " " << k << " " << i << " " << j << endl;
						if (poids[i][j] < poids[i][k] * aretes[k][j]) {
							poids[i][j] = poids[i][k] * aretes[k][j];
							antecedent[i][j] = k;
						}
						j++;

					}
					//cerr << "poids : " << i << " " << fixed << setprecision(3) << poids[i][i] << endl;
					if (poids[i][i] >= 1.01) {
						b = false;
						length = k+2;
						depart = i;
					}
					i++;
				}
				k++;
			}

			a++;
		}

		cerr << length << " " << depart+1 << " " << (poids[depart][depart]-1)*100 << endl;
		cerr << "debug\n";
		// à ce stade, on sait d'où part le cycle de poids > 1 de taille minimale ainsi que sa taille
		// on va donc parcourir le graphe à partir de depart pour chercher à retomber sur depart avec une taille length et un poids >1
		vector<int> chemin;
		chemin.push_back(depart);
		if (length == -1)
			cout << "no arbitrage sequence exists\n";
		else if (poids[depart][depart] < 1.01)
			cout << "no arbitrage sequence exists\n";
		else {
			int ante = depart;
			chemin.push_back(ante);
			ante = antecedent[depart][depart];
			while (ante != depart) {
				chemin.push_back(ante);
				ante = antecedent[depart][ante];
			}

			int indm = 0;
			int mini = chemin[0];

			int m = chemin.size();
			for (int i = 1; i < m; i++) {
				if (chemin[i] < mini) {
					indm = i;
					mini = chemin[i];
				}
			}
			for (int k = indm; k > 0; k--)
				cout << chemin[k]+1 << " ";
			for (int k = m-1; k >= indm; k--) 
				cout << chemin[k]+1 << " ";

			double gainF;
			gainF = (poids[depart][depart]-1)*100;
			cout << fixed << setprecision(3) << gainF << "%" << endl;

		}
	}
	return 0;
}