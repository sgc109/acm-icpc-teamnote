struct Point{
    ll x, y;
    Point operator-(Point rhs){
        return Point{x - rhs.x, y - rhs.y};
    }
    ll dot(Point rhs){
        return x * rhs.y - y * rhs.x;
    }
};
struct Line{
    Point p1, p2;
};
int ccw(Point a, Point b, Point c){
    ll cw = (a - c).dot(b - c);
    if(!cw) return 0;
    cw /= abs(cw);
    return (int)cw;
}
int isOver(Line l1, Line l2){
    int cw1 = ccw(l2.p1, l1.p2, l1.p1);
    int cw2 = ccw(l1.p2, l2.p2, l1.p1);
    int cw3 = ccw(l1.p2, l2.p2, l2.p1);
    int cw4 = ccw(l2.p2, l1.p1, l2.p1);
    if(cw1 * cw2 > 0 && cw3 * cw4 > 0) return 1;
    return 0;
}
