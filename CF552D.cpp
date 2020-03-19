// Vanya and Triangles

#include <iostream>
using namespace std;

// This is the brute force approach. Check all the pair of three 
// points to see if they form a triangle or not

int main(){
    int N;
    cin >> N;
    int xx[N], yy[N];
    for(int i = 0; i < N; i++)
        cin >> xx[i] >> yy[i];
    int count = 0;
    for(int i = 0 ; i < N; i++){
        for(int j = i+1 ; j < N; j++){
            for(int k = j+1 ; k < N; k++){
                int x1 = (xx[i] - xx[j]);
                int y1 = (yy[i] - yy[j]);
                int x2 = (xx[i] - xx[k]);
                int y2 = (yy[i] - yy[k]);
                if(x1 * y2 - y1 * x2 != 0) count++;
            }
        }
    }
    cout << count << endl;
    return 0;
}