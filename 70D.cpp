// 70D Online incremenetal convex hull

#include <iostream>
#include <map>
using namespace  std;

typedef long long ll;

ll cross3(pair<int, int> i, pair<int, int> j, pair<int, int> k){
    ll x1 = i.first - j.first;
    ll y1 = i.second - j.second;
    ll x2 = i.first - k.first;
    ll y2 = i.second - k.second;
    return x1 * y2 - x2 * y1;
}


// evaluate whether the point x, y lies on convex hull or outside it
bool inHull(map<int, int>& hull, int x, int y){
    // Can not lie on a hull if it's empty
    if (hull.size() == 0) return false;

    // if x is in hull, new y should be greater to be added to the hull
    if (hull.find(x) != hull.end()) return (hull[x] <= y);

    // if the value of x is outside of min x and max x -> false
    int minx = hull.begin()->first;
    int maxx = prev(hull.end())->first;
    if (!(minx <= x && maxx >= x)) return false;

    // find two points left of it.
    auto a = pair<int, int>(x, y);
    auto c = hull.lower_bound(x);
    auto b = prev(c);
    // cout << b->first << " : " << b->second << ", " << c->first << " : " << c->second << endl;
    return cross3(a, *b, *c) >= 0;
}

void add(map<int, int>& hull, int x, int y){
    if (inHull(hull, x, y) == true) return;

    // Insert the point x, y
    hull[x] = y;

    // pointer to the right most instance of x
    auto i = prev(hull.upper_bound(x));

    // Remove all points on left which may now lie inside the hull
    // Compute cross for two points left of current point and repeat
    auto j = prev(i);
    auto k = prev(j);
    while(i != hull.begin() && j != hull.begin() && cross3(*j, *i, *k) <= 0){
        hull.erase(j);
        j = k;
        k = prev(k);
    }

    // Remove right points which may now lie inside the hull
    // Compute cross for two points right of current point and repeat
    j = next(i);
    k = next(j);
    while (j != hull.end() && k != hull.end() && cross3(*j, *i, *k) >= 0){
        hull.erase(j);
        j = k;
        k = next(k);
    }
}

int main(){
    // upper hull and lower hull. Map keeps the pairs sorted in ascending order
    map<int, int> lower, upper;

    int N;
    cin >> N;
    pair<int, int> p = pair<int, int>(2, 3);
    // print_keys(p);
    int query, x, y;
    for(int _ = 0; _ < N; _++){
        cin >> query >> x >> y;
        if (query == 1){
            add(upper, x, y);
            add(lower, x, -y);
        } else {
            bool res = inHull(upper, x, y) && inHull(lower, x, -y);
            if (res) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    } //
    return 0;
}