//660D. Number of parallelograms

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x = 0, y = 0;

    bool operator<(Point& a) const {
        if (a.x != x) {
            if (a.x < x) return true;
            else return false;
        } else {
            if (a.y < y) return true;
            else return false;
        }
    }
};


int main() {
    // Read inputs
    int N;
    cin >> N;
    vector <Point> points(N);
    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
    }

    // Compute midpoints
    int M = N * (N - 1) / 2;
    int k = 0;
    vector <Point> midpoints(M);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Avoid dividing by 2 to obtain midpoint because that's just waste of time
            midpoints[k].x = points[i].x + points[j].x;
            midpoints[k].y = points[i].y + points[j].y;
            k++;
        }
    }

    // Sort the mid points. Sorted in reverse order
    sort(midpoints.begin(), midpoints.end());

    // Count the number of parallelograms
    int count = 0; // Number of continuous duplicates
    int pairs = 0; // Number of parallelograms
    for (int i = 0; i < M; i++) {
        if (i < M - 1 and midpoints[i].x == midpoints[i - 1].x and midpoints[i].y == midpoints[i - 1].y) {
            count += 1;
        } else {
            pairs += count * (count - 1) / 2;
            count = 1;
        }
    }
    cout << pairs;
    return 0;
}
