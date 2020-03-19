//O. Arrow
#include<iostream>
#include<stdio.h>
#include<cmath>
using namespace std;

int main(){
    double px, py, vx, vy, a, b, c, d;
    cin >> px >> py >> vx >> vy >> a >> b >> c >> d;
    cout.precision(12);

    // Normalize the vector
    double l = sqrt((vx * vx) + (vy * vy));
    vx /= l;
    vy /= l;

    // The first point at the top
    cout << px + vx * b << " " << py + vy * b << endl;

    // The left half of the arrow
    cout << px - vy * a / 2.0 << " " << py + vx * a / 2.0 << endl;
    cout << px - vy * c / 2.0 << " " << py + vx * c / 2.0 << endl;
    cout << px - vy * c / 2.0 - vx * d << " " << py + vx * c / 2.0 - vy * d << endl;

    // The symmetric right
    cout << px + vy * c / 2.0 - vx * d << " " << py - vx * c / 2 - vy * d << endl;
    cout << px + vy * c / 2.0 << " " << py - vx * c / 2.0 << endl;
    cout << px + vy * a / 2.0 << " " << py - vx * a / 2.0 << endl;
    return 0;
}