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
        Node *l, *r;
        int v;
        Node(Node *l, Node *r, int v):l(l),r(r),v(v){}

    };
    vector<Node *> tree;
    int N;
    int MIN_VAL = 0, MAX_VAL = 1000000 - 1;
    PST(vector<int>& v){
        N = sz(v);
        tree.resize(N + 1);
        tree[0] = new Node(0, 0, 0);
        tree[0]->l = tree[0]->r = tree[0];
        for(int i = 1; i <= N; i++) {
            tree[i] = makeTree(0, MAX_VAL - MIN_VAL, v[i - 1], tree[i - 1]);
        }
    }
    Node *makeTree(int nl, int nr, int idx, Node *now){
        if(nr < idx || idx < nl) return now;
        if(nl == nr) return new Node(0, 0, now->v + 1);
        int nm = nl + nr >> 1;
        Node *tl = makeTree(nl, nm, idx, now->l);
        Node *tr = makeTree(nm + 1, nr, idx, now->r);
        Node *cur = new Node(tl, tr, tl->v + tr->v);
        return cur;
    }

    int query(int nl, int nr, int l, int r, Node *now){
        if(r < nl || nr < l) return 0;
        if(l <= nl && nr <= r) return now->v;
        int nm = nl + nr >> 1;
        return query(nl, nm, l, r, now->l) + query(nm + 1, nr, l, r, now->r);
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
        nxt[i] = lst ? lst : N;
        mp[A[i]] = i;
    }
    PST pst(nxt);
    cin >> Q;
    while(Q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << pst.query(0, N - 1, r, N - 1, tree[r + 1]) - pst.query(0, N - 1, r, N - 1, tree[l]) << '\n';
    }
}

