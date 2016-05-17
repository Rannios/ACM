#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> intVect;


void LDS(const vector<int> &x, vector<int> &b) // fonction prise dans le cours
{
  if(x.empty()) return;

  //tableau des predecesseurs pour la reconstruction
  vector<int> p(x.size());
  vector<int> m(1,0);

  for(int i=1; i < int(x.size()); ++i)
  {
    //si x[i] augmente la LDS courante
    if(x[i] <= x[m.back()])
    {
      p[i]=m.back();
      m.push_back(i);
      continue;
    }

    //sinon recherche dichotomique
    int lo = 0, hi = m.size()-1;
    while(lo != hi)
    {
      int mid = (lo+hi)/2;
      if(x[m[mid]] >= x[i]) { lo = mid+1; }
      else { hi = mid; }
    }

    //mise a jour du predecesseur
    p[i] = m[lo-1];
    //et si besoin de la LIS que fini x[i]
    if(x[i] >= x[m[lo]]) m[lo] = i;
  }

  //creation de la solution
  int curr = m.back();
  int i = m.size();
  while(i--)
  {
    b.push_back(x[curr]);
    curr=p[curr];
  }

  reverse(b.begin(), b.end());
}

int main()
{
    int n(0);
    int line;


    while(cin >> line && line > -1) // for each test
    {
        if(n != 0) { cout << "\n"; }
        n++;
        intVect altitudes(1, line);
        intVect b(0);

        while(cin >> line && line > -1) // for each missile
        {
            altitudes.push_back(line);
        }

        LDS(altitudes, b);

        cout << "Test #" << n << ":\n  maximum possible interceptions: " << b.size() << "\n";
    }

    return 0;
}
