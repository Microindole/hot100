#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, a;
    double m = 0;
    cin>> n>> a;
    for(int i = 0;i<n;i++){
        double x,y;
        cin >> x>>y;
        if ((x*x + y*y)<=(a*a)){
            m++;
        }
    }

    cout << 4.0*m / (double)n <<endl;
}