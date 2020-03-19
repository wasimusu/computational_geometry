// Online diameter -- rotating callipers
#include <iostream>
#include <map>
using namespace  std;

typedef long long ll;
bool change;

inline ll cross3(pair<int, int> i, pair<int, int> j, pair<int, int> k){
    return (ll)(i.first - j.first) * (i.second - k.second) - (ll)(i.first - k.first) * (i.second - j.second);    
}

inline ll distance(int x1, int y1, int x2, int y2){
    return (ll)(x1 - x2) * (x1 - x2) + (ll)(y1 - y2) * (y1 - y2);
}

// evaluate whether the point x, y lies on convex hull or outside it
bool inHull(map<int, int>& hull, int x, int y){
    // Can not lie on a hull if it's empty
    if (hull.size() == 0) return false;
    
    // if x is in hull, new y should be greater to be added to the hull
    if (hull.find(x) != hull.end()) return (hull[x] <= y);

    // if the value of x is outside of min x and max x -> false
    if (!(hull.begin()->first <= x && prev(hull.end())->first >= x)) return false; 

    // find two points left of it.
    auto c = hull.lower_bound(x);
    auto b = prev(c);
    return cross3(pair<int, int>(x, y), *b, *c) >= 0;     
}

void add(map<int, int>& hull, int x, int y){
    if (inHull(hull, x, y) == true) return;

    // Insert the point x, y
    hull[x] = y;
    change = true;
    
    // pointer to the right most instance of x
    auto i = prev(hull.upper_bound(x)); 
    
    // Remove all points on left which may now lie inside the hull
    auto j = prev(i);
    auto k = prev(j);
    while(i != hull.begin() && j != hull.begin() && cross3(*j, *i, *k) <= 0){
        hull.erase(j);
        j = k;
        k = prev(k);
    }

    // Remove right points which may now lie inside the hull
    j = next(i);
    k = next(j);
    while (j != hull.end() && k != hull.end() && cross3(*j, *i, *k) >= 0){
        hull.erase(j);
        j = k;
        k = next(k);
    }
}

ll diameter(map<int, int>& lower, map<int, int>& upper){
    ll maxd = 0;
    for(auto i: upper){
        for(auto j: upper){
            maxd = max(maxd, distance(i.first, i.second, j.first, j.second));            
        }
    }
    for(auto i: lower){
        for(auto j: lower){
            maxd = max(maxd, distance(i.first, i.second, j.first, j.second));            
        }
    }
    for(auto i: upper){
        for(auto j: lower){
            maxd = max(maxd, distance(i.first, i.second, j.first, -j.second));            
        }
    }
    return maxd;
}

int main(){
    // upper hull and lower hull. Map keeps the pairs sorted in ascending order
    map<int, int> lower, upper; 
    
    int N;
    cin >> N;
    int x, y;
    ll dist = 0;
    for(int _ = 0; _ < N; _++){
        change = false;
        cin >> x >> y;
        add(upper, x, y);
        add(lower, x, -y);
        if (change) dist = diameter(upper, lower);
        cout << dist << endl;
    }
    return 0;
}