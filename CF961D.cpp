// Pair of Lines

#include<iostream>
#include<set>
#include<vector>
using namespace std;


long long cross(long x1, long y1, long x2, long y2){
    return (long long)x1 * y2 - (long long)y1 * x2;
}

bool areTwoLines(vector<long> xx, vector<long> yy, int i, int j){
    int N = xx.size();
    set<int> used;
    used.insert(i);
    used.insert(j);
    long ax = xx[i] - xx[j];
    long ay = yy[i] - yy[j];
    long bx, by;
    for(int k = 0; k < N; k++){
        if (used.find(k) != used.end())
            continue;
        bx = xx[i] - xx[k];
        by = yy[i] - yy[k];
        if (cross(ax, ay, bx, by) == 0) used.insert(k);
    }

    // Compute the remaining points
    vector<int> rem;
    for(int i = 0; i < N; i++){
        if (used.find(i) == used.end()){
            rem.push_back(i);
        }
    }
    // If there are only two points they must lie on one line
    if (rem.size() <= 2) return true;

    i = rem[0];
    j = rem[1];
    ax = xx[i] - xx[j];
    ay = yy[i] - yy[j];

    int k;
    for(int p = 2; p < rem.size(); p++){
        k = rem[p];
        bx = xx[i] - xx[k];
        by = yy[i] - yy[k];
        if (cross(ax, ay, bx, by) != 0) return false;
    }

    return true;
}

int main(){
    // Read inputs
    int N;
    cin >> N;
    if(N <= 3) {
        cout << "YES";
        return 0;
    }
    vector<long> xx, yy;
    long x, y;
    for(int i = 0; i < N; i++){
        cin >> x >> y;
        xx.push_back(x);
        yy.push_back(y);
    }

    // The three starting points
    int i = 0, j = 1, k = 2;

    if (areTwoLines(xx, yy, i, j) == true) {
        cout << "YES";
        return 0;
    }
    if (areTwoLines(xx, yy, i, k) == true){
        cout << "YES";
        return 0;
    }
    if (areTwoLines(xx, yy, j, k) == true){
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}