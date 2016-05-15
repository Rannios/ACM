#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <stack>

using namespace std;

typedef vector<int> intVect;
typedef vector<bool> boolVect;

bool acceptable(int p, int n, boolVect &dead_led, vector<intVect> &table)
{
    for(int i=0; i<n; i++)
    for(int j=i+1; j<n; j++) // compare each figure with all the others
    {
        bool ambiguous = true;
        for(int k=0; k<p && ambiguous; k++) // for each LED
            if(!dead_led[k] && table[i][k] != table[j][k]) // the LED is not the same for i and j
                ambiguous = false;

        if(ambiguous) { return false; }
    }

    return true;
}

void printTable(vector<bool> &t)
{
    for(int i=0; i<t.size(); i++)
        cout << t[i] << " ";
}

int main()
{
    int nb_pb, p, n, tmp;
    cin >> nb_pb;
    while(nb_pb > 0)
    {
        nb_pb --;
        cin >> p >> n;

        vector<intVect> table(n);

        if(!p || !n) { cout << p << endl; break; }

        for(int i=0; i<n; i++) // create the table of 0s and 1s
        {
            for(int j=0; j<p; j++)
            {
                cin >> tmp;
                (table[i]).push_back(tmp);
            }
        }

        int max_deletable_leds(0);
        stack<int> modif;
        boolVect leds(p, false); // true for dead LEDs
        tmp = -1;

        while(tmp < p-1)
        {
            modif.push(tmp+1); leds[tmp+1] = true;

            if(acceptable(p, n, leds, table))
            {
                max_deletable_leds = max(max_deletable_leds, (int)modif.size());
                tmp = modif.top();

                if(tmp+1 >= p)
                {
                    modif.pop(); leds[tmp] = false;
                    if(modif.empty()) { break; } // every case has been watched
                    tmp = modif.top();
                    modif.pop(); leds[tmp] = false;
                }
            }
            else // the entire branch is unacceptable
            {
                tmp = modif.top();
                modif.pop(); leds[tmp] = false;

                if(tmp+1 >= p)
                {
                    if(modif.empty()) { break; }
                    tmp = modif.top();
                    modif.pop(); leds[tmp] = false;
                }
            }
        }

        cout << (p-max_deletable_leds);
        if(nb_pb ||1) cout << endl;
    }

    return 0;
}
