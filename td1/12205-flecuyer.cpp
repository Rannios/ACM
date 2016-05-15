#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    int N, M;
    while(cin >> N >> M && (N != 0 || M !=0))
    {
        vector<int> convStart(N,0), convDur(N,0), convFin(N,0);
        vector<int> listenStart(M, 0), listenDur(M, 0), listenFin(M, 0);
        vector<int> active(M, 0); // each listening session has no active call at the beginning
        int useless, useless2;



        for(int i(0); i<N; i++) // for each call
        {
            //cout << "lol" << endl;
            cin >> useless >> useless2 >> convStart[i] >> convDur[i];
            convFin[i] = convStart[i] + convDur[i];
            //cout << "mdr" << endl;
        }
        for(int i(0); i<M; i++) // for each listening session
        {
            cin >> listenStart[i] >> listenDur[i];
            listenFin[i] = listenStart[i] + listenDur[i];

            for(int j(0); j<N; j++) // {}: listen, []: call
            {
                if(     (listenStart[i] < convFin[j] && listenFin[i] >= convFin[j])         //  [ { ]} or { [] }
                    ||  (listenStart[i] <= convStart[j] && listenFin[i] > convStart[j])     //  {[ } ]
                    ||  (listenStart[i] >= convStart[j] && listenFin[i] <= convFin[j]) )    //  [ {} ]
                {
                    active[i] ++;
                }
            }
            cout << active[i] << endl;
        }
    }



    return 0;
}
