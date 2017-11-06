/*
addPoint 로 점들을 추가하고
makeConvex 함수를 한번 호출해주면
멤버 변수인 poly에 컨벡스헐을 구성하는
점들이 들어있게된다.
*/
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
struct Convexhull{
    vector<Point> poly;
    vector<Point> ps;
    void addPoint(ll x, ll y){
        ps.pb(Point{x, y});
    }
    void makeConvex(){
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
        this->poly = poly;
    }
};
int N;
int main(){
    fastio();
    cin >> N;
    Convexhull convex;
    for(int i = 0; i < N; i++){
        ll x, y;
        cin >> x >> y;
        convex.addPoint(x, y);
    }
    convex.makeConvex();
    auto poly = convex.poly;
    if(sz(poly) <= 2) return !printf("0");
    cout << sz(poly);
}
