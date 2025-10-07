#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct State {
    int i, f;
    long long d;
    
    bool operator==(const State& o) const {
        return i == o.i && f == o.f && d == o.d;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        return ((size_t)s.i << 40) ^ ((size_t)s.f << 20) ^ (size_t)min(s.d, 100000LL);
    }
};

int n;
vector<long long> s;
unordered_map<State, long long, StateHash> memo;

long long solve(int i, int f, long long d) {
    if (i > f) return 0;
    
    State st = {i, f, d};
    auto it = memo.find(st);
    if (it != memo.end()) return it->second;
    
    long long e = s[i] - d;
    if (e <= 0) {
        long long res = solve(i + 1, f, 1);
        memo[st] = res;
        return res;
    }
    
    long long r = 1e18;
    for (int j = i; j <= f; j++) {
        long long ej = s[j] - (j == i ? d : 0);
        if (ej <= 0) continue;
        
        long long c = ej;
        if (j > i) {
            c += solve(i, j - 1, d);
            if (c >= r) continue;
        }
        if (j < f) c += solve(j + 1, f, j - i + 1);
        r = min(r, c);
    }
    
    memo[st] = r;
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    s.resize(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    cout << solve(0, n - 1, 0) << "\n";
    return 0;
}