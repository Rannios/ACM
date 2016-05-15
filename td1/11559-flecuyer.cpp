#include <iostream>
#include <string>
#include <sstream>
#define BUDGET_MAX 500000

using namespace std;

int main()
{
    int N(200), B(BUDGET_MAX), H(18), W(13);
    string line;
    int p(10000); // price of hotels
    int a(1000); // available beds
    int cost;

    while(cin >> N >> B >> H >> W) // for each input
    {
        cost = BUDGET_MAX+1;


        for(int i(0); i<H; i++) // for each hotel
        {
            bool hotel_ok = false;
            cin >> p; // price per person

            cin.ignore();
            getline(cin, line);
            stringstream weeksLine(line);

            if(p*N <= B) // if not too expensive
            {
                for(int j(0); j<W; j++) // for each week
                {
                    weeksLine >> a;
                    if(a >= N) // enough beds
                    {
                        hotel_ok = true;
                        break;
                    }
                }
            }
            if(hotel_ok)
            {
                cost = min(cost, p*N);
            }
        }

        if(cost > BUDGET_MAX) // stay home
        {
            cout << "stay home" << endl;
        }
        else
        {
            cout << cost << endl;
        }
    }
    return 0;
}

