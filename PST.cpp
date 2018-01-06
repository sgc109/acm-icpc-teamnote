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

struct PST{
    struct Node{
        int l, r, v;
        Node():l(0),r(0),v(0){}
        Node(int l, int r, int v):l(l),r(r),v(v){}
    };
    vector<Node> nodes;
    vector<int> tree;
    int N, acc;
    int MIN_VAL = 0, MAX_VAL = 1000000 - 1;
    PST(vector<int>& v){
        N = sz(v);
        MAX_VAL = N - 1;
        tree.resize(N + 1);
        nodes.resize(22 * N);
        for(int i = 1; i <= N; i++) {
            tree[i] = makeTree(0, MAX_VAL - MIN_VAL, v[i - 1], tree[i - 1]);
        }
    }
    int makeTree(int nl, int nr, int idx, int now){
        if(nr < idx || idx < nl) return now;
        if(nl == nr) return nodes[++acc] = Node(0, 0, nodes[now].v + 1), acc;
        int nm = nl + nr >> 1;
        int tl = makeTree(nl, nm, idx, nodes[now].l);
        int tr = makeTree(nm + 1, nr, idx, nodes[now].r);
        return nodes[++acc] = Node(tl, tr, nodes[tl].v + nodes[tr].v), acc;
    }

    int query(int nl, int nr, int l, int r, int now){
        if(r < nl || nr < l) return 0;
        if(l <= nl && nr <= r) return nodes[now].v;
        int nm = nl + nr >> 1;
        return query(nl, nm, l, r, nodes[now].l) + query(nm + 1, nr, l, r, nodes[now].r);
    }
    int query(int tl, int tr, int l, int r){
        return query(0, MAX_VAL - MIN_VAL, l, r, tree[tr + 1]) - query(0, MAX_VAL - MIN_VAL, l, r, tree[tl]);
    }
};


int N, Q;
int A[1000003];
vector<int> nxt;
map<int,int> mp;
int main(){
    fastio();
    cin >> N;
    nxt.resize(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = N - 1; i >= 0; i--) {
        int lst = mp[A[i]];
        nxt[i] = (lst ? lst : N) - 1;
        mp[A[i]] = i;
    }
    PST pst(nxt);
    cin >> Q;
    while(Q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << pst.query(l, r, r, N - 1) << '\n';
    }
}
