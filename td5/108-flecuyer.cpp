#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

typedef vector<vector<int>> sMatrix;

int main()
{
    int N;
    while(cin >> N)
    {
        sMatrix matix(N);
        for(int i=0; i<N; i++)
        for(int j=0, tmp; j<N; j++)
        {
            cin >> tmp;
            (matix[i]).push_back(tmp);
        }

        sMatrix prefix_sum(N);                  // prefix_sum[i][j] = sum for l=0 to j-1 of matix[i][l]
        for(int i=0; i<N; i++)                  //                  = sum of cells 0 to j-1 in row i
        for(int j=0, cumul=0; j<=N; j++)
        {
            (prefix_sum[i]).push_back(cumul);
            cumul += matix[i][j];
        }

        int best(prefix_sum[0][0]);
        for(int j=1; j<=N; j++)                 // first column of the recangle
        for(int l=j; l<=N; l++)                 // last column
        for(int i=0, sum=0; i<N; i++)           // rows
        {
            sum = max(sum, 0);                  // do not take the precedent rows if their sum is negative
            sum += (prefix_sum[i][l]-prefix_sum[i][j-1]); // sum of cells j to l in row i
            best = max(best, sum);
        }

        cout << best << endl;
    }

    return 0;
}
