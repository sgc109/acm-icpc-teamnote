#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
#define fastio() ios::sync_with_stdio(0),cin.tie(0);
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int inf = 0x3c3c3c3c;
const ll infl = 0x3c3c3c3c3c3c3c3c;

struct Point{
    ll x, y;
    Point operator+(Point& rhs){
        return Point{x + rhs.x, y + rhs.y};
    }
    Point operator-(Point& rhs){
        return Point{x - rhs.x, y - rhs.y};
    }
    bool operator<(Point& rhs){
        if(x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
    ll cross(Point rhs){
        return x * rhs.y - y * rhs.x;
    }
    ll size(){
        return x * x + y * y;
    }
};
int ccw(Point a, Point b, Point c){
    ll cw = (c - a).cross(c - b);
    if(!cw) return 0;
    cw /= abs(cw);
    return cw;
}
vector<Point> makeConvex(vector<Point>& ps){
    int n = sz(ps);
    sort(all(ps));
    Point st = ps[0];
    ps.erase(ps.begin());
    auto cmp = [&](Point& a, Point& b){
        int cw = ccw(a, b, st);
        if(!cw) (a - st).size() < (b - st).size();
        return cw > 0;
    };
    sort(all(ps), cmp);
    vector<Point> poly;
    poly.pb(st);
    for(int i = 0; i < sz(ps); i++){
        while(sz(poly) >= 2 && ccw(poly.back(), ps[i], poly[sz(poly) - 2]) <= 0) poly.pop_back();
        poly.pb(ps[i]);
    }
    return poly;
}
int N;
vector<Point> ps;
int main(){
    fastio();
    cin >> N;
    for(int i = 0; i < N; i++){
        ll x, y;
        cin >> x >> y;
        ps.pb(Point{x, y});
    }
    vector<Point> convex = makeConvex(ps);
    if(sz(convex) <= 2) return !printf("0");
    cout << sz(convex);
}
