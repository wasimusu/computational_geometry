#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int xx[1000], yy[1000];
int N;

long long cross(int i, int j, int k){
    long long x1 = xx[j] - xx[i];
    long long y1 = yy[j] - yy[i];
    long long x2 = xx[k] - xx[i];
    long long y2 = yy[k] - yy[i];
    return x1 * y2 - x2 * y1;
}

bool canBeTower(int x1, int x2, int N){
    int ax = xx[0];
    xx[0] = x1;

    bool res = true;
    for(int i = 2; i + 1 < N; i++){
        ll left = cross(i, i + 1, 0);
        ll right = cross(i, i + 1, 0);
        if (left > 0 && right > 0){
            res = false;
            break;
        }
    }

    xx[0] = ax;
    return res;
}

int lowerBound(vector<int>& arr, int N){
    int left = 0, right = arr.size() - 1;
    while(left <= right){
        int m = (int)(left + right)/2;
        m = arr[m];
        if (canBeTower(m, m, N)){
            right = m;
        } else {
            left = m + 1;
        }
    }
    return left;
}

int main(){
    cin >> N;
    for(int i = 0; i < N; i++) cin >> xx[i] >> yy[i];

    // Zero center the points
    bool flip = xx[0] < xx[1];
    int x = xx[0], y = yy[0];
    for(int i = 0; i < N; i++){
        xx[i] -= x;
        yy[i] -= y;
    }

    int left = min(xx[0], xx[1]);
    int right = max(xx[0], xx[1]);
    int total = 0;

    // Lower and upper bound on indices
    vector<int> arr;
    for(int i = left; i <= right; i++) arr.push_back(i);

/*
    // Binary search to find upper and lower bounds has error

    int lower = lowerBound(arr, N);
    reverse(arr.begin(), arr.end());
    int upper = arr.size() - 1 - lowerBound(arr, N);
*/

    // Brute force way to find lower and upper bound
    int lower = 0, upper = arr.size() - 1;
    while (lower < upper && canBeTower(arr[lower], arr[lower], N) == false) lower++;
    while (lower < upper && canBeTower(arr[upper], arr[upper], N) == false) upper--;

    bool l = canBeTower(arr[lower], arr[lower], N);
    bool r = canBeTower(arr[upper], arr[upper], N);

    total = upper - lower + 1;
    if ((l && r) == false){
        total = 0;
        if (l) total++;
        if (r) total++;
    }
    cout << total << endl;
    return 0;
}//
// Created by A02290691 on 3/19/2020.
//

