

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

long long cross(const int x1, const int y1, const int x2, const int y2){
    return (long long)x1 * y2 - (long long)x2 * y1;
}

long double distance(const int x1, const int y1, const int x2, const int y2){
    return sqrt((long long)(x1 - x2) * (x1 - x2) + (long long)(y1 - y2) * (y1 - y2));
}

int main(){
    int N;
    cin >> N;
    int xx[N], yy[N];
    cout.precision(10);
    for(int i = 0; i < N; i++)
        cin >> xx[i] >> yy[i];

    int x1, x2, y1, y2;
    long double min_height = 100000000000000000000.0;
    for(int i = 0; i < N; i++){
        x1 = xx[(i+1)%N] - xx[i];
        y1 = yy[(i+1)%N] - yy[i];
        x2 = xx[(i+1)%N] - xx[(i + 2) % N];
        y2 = yy[(i+1)%N] - yy[(i + 2) % N];
        long double height = 1.0 * cross(x1, y1, x2, y2) / distance(xx[i], yy[i], xx[(i + 2) % N], yy[(i + 2) % N]);
        min_height = (height < min_height) ? height : min_height;
    }
    cout << min_height/2.0 << endl;

    return 0;
}