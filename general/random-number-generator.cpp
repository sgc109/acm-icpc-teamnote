int main(){
    fastio();
    mt19937 rng(time(0));
    for(int i = 0; i < 100; i++) {
        cout << rng() << '\n';
    }
}
