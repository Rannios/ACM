#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std;

void print_stack(stack<int> s, bool out)
{
    stack<int> mdr;
    while(!s.empty())
    {
        mdr.push(s.top());
        s.pop();
    }
    cout << mdr.top(); mdr.pop();
    while(!mdr.empty())
    {
        cout << " " << mdr.top();
        mdr.pop();
    }

    if(out) cout << endl;
}

void checkCircle(const vector<int> &isPrime, const int n, stack<int> &circle, vector<int> &used, int trial)
{
    if(circle.size() >= n) // full circle
    {
        if(isPrime[ circle.top()+1 ]) // successful circle
            print_stack(circle, 1);
    }
    else if(used[trial]) { } // trial is already used in the circle
    else if(circle.empty() || isPrime[trial+circle.top()] )
    {
        circle.push(trial); // the trial is accepted
        used[trial] = true;
        for(int i=1; i<=n && (circle.size()<n || i==1); i++) // go to next step with any other trial
        {
            checkCircle(isPrime, n, circle, used, i);
        }
        circle.pop(); // remove "trial" from the stack
        used[trial] = false;
    }
}

int main()
{
    // create a vector which says whether an integer is prime or not
    vector<int> isPrime(40,false);
    vector<int> prime{2,3,5,7,11,13,17,19,23,29,31,37};
    for(int i=0; i<prime.size(); i++)
        isPrime[prime[i]] = true;


    int n; // bound
    int counter(0);

    while(cin >> n) // for each case
    {
        if(counter > 0) cout << endl;
        cout << "Case "<<(++counter)<<":"<<endl;

        if(n == 1) { cout << "1\n"<<endl; continue; } // trivial case
        if(n%2 == 1) { cout << endl; continue; } // if n is odd, there is no hope

        int tmp;
        stack<int> circle;
        vector<int> used(n+1, false);

        checkCircle(isPrime, n, circle, used, 1); // try a circle which begins with 1
    }

    return 0;
}

