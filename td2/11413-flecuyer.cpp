#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool acceptable_capacity(int c, int n, int m, vector<int> &vessel)
{
    int j=0; // j = vessel
    for(int i=0; i<m; i++) // i = container to fill
    {
        int ctmp = 0; // current volume in the container i
        while(j<n && ctmp + vessel[j] <= c) // fill this container with the vessel j
        {
            ctmp += vessel[j];
            j++;
        }
    }
    return (j >= n); // true if every vessel has a container
}

int main()
{
    int n; // number of vaissels
    int m; // number of containers
    bool first(false);

    while(cin >> n >> m) // for each case
    {
        vector<int> vessel(n);
        int totalVolume = 0; // total volume of vessels
        int maxVessel = 0; // biggest vessel

        for(int i=0; i<n; i++) // for each capacity
        {
            cin >> vessel[i];
            maxVessel = max(maxVessel, vessel[i]);
            totalVolume += vessel[i];
        }

        if(n <= m) // particular case where there are less vessels than containers
        {
            cout << maxVessel << endl; continue;
        }
        int lowerBound(0), upperBound(totalVolume);
        int current;

        while(lowerBound+1 < upperBound)
        {
            current = (lowerBound + upperBound) / 2;

            if(acceptable_capacity(current, n, m, vessel))
                upperBound = current;
            else
                lowerBound = current;
        }

        cout << (acceptable_capacity(lowerBound, n, m, vessel)? lowerBound:upperBound) << endl;
    }

    return 0;
}
