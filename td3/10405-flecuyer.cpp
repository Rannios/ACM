#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Dynamic Programming

    for all i belonging to [1, size of a]
    for all j belonging to [1, size of b]

    let us define :
    s(i, 0) = 0
    s(0, j) = 0
    s(i, j) =
        | si a[i] == b[j] : s(i-1, j-1)+1
        | sinon : max( s(i-1, j), s(i, j-1) )
*/

int main()
{
    string a, b;
    while(getline(cin, a) && getline(cin, b))
    {
        int la = a.length(), lb = b.length();
        vector<vector<int>> s(la+1);

        for(int j=0; j<lb+1; j++)
            (s[0]).push_back(0);
        for(int i=1; i<la+1; i++)
        {
            (s[i]).push_back(0);
            for(int j=1; j<lb+1; j++)
            {
                if(a[i-1] == b[j-1])
                    (s[i]).push_back( 1 + s[i-1][j-1] );
                else
                    (s[i]).push_back( max( s[i-1][j], s[i][j-1] ) );
            }
        }

        cout << s[la][lb] << endl;
    }

    return 0;
}
