#include <iostream>
#include <string>

using namespace std;

int main()
{
    bool open(false);
    string line;

    while(getline(cin, line))
    {
        for(int i(0); i<line.size(); i++)
        {
            if(line[i] == '"')
            {
                if(!open)
                {
                    open = true;
                    cout << "``";
                }
                else
                {
                    open = false;
                    cout << "''";
                }
            }
            else
            {
                cout << line[i];
            }
        }
        cout << endl;
    }
    return 0;
}
