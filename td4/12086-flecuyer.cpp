#include <iostream>
#include <string>
#include <vector>

using namespace std;


int somme(int x, int y, const vector<int> & t)
{
    if(x==0)
    {
        int res=0;
        while(y>=0)
        {
            res+=t[y];
            y=(y&(y+1))-1;
        }
        return res;
    }
    else
        return somme(0,y,t)-somme(0,x-1,t);
}

void incremente(int x, int inc, vector<int> & t)
{
    while(x<int(t.size()))
    {
        t[x]+=inc;
        x=x|(x+1);
    }
}


int main()
{
    int N;
    while(cin >> N && N)
    {
        vector<int> podo(N);
        vector<int> prefix_sum(N);
        vector<int> erase_sum(N);
        int sum = 0;

        for(int i=0; i<N; i++)
        {
            cin >> podo[i];
            sum += podo[i];
            prefix_sum[i] = sum;
        }

        for(int i=0; i<N; i++)
        {
            for(int j= i&(i+1); j<=i; j++)
                erase_sum[i] += podo[j];
        }

        string action;
        while(cin >> action && action != "END")
        {
            int p1, p2;
            cin >> p1 >> p2;
            if(action == "S")
            {
                p1--;
                int diff = p2 - podo[p1];
                podo[p1] = p2;
                incremente(p1, diff, erase_sum);
            }
            else if(action == "M")
            {
                p1--; p2--;
                cout << somme(p1,p2,erase_sum) << endl;
            }
        }
    }

    return 0;
}

