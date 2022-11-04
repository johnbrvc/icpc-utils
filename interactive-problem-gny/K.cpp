// Opgave: K

#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <ll, ll> ii;
typedef vector <ll> vi;
typedef vector <vi> vvi;
typedef vector <ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i, a, b) for(auto i=(a); i<(b); ++i)
#define REP(i, n) rep(i,0,n)
#define all(v) begin(v), end(v)
#define sz(v) ((int) (v))
#define rs resize
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl;

void run();

template<class T>
ostream &operator<<(ostream &os, const vector <T> &v) {
    os << "[";
    for (const T &x : v) os << x << ',';
    return os << "]";
}

namespace std {
    template<class T1, class T2>
    struct hash<pair < T1, T2>> {
    public:

    size_t operator()(const pair <T1, T2> &p) const {
        size_t x = hash<T1>()(p.x), y = hash<T2>()(p.y);
        return x ^ (y + 0x9e3779b9 + (x << 6) + (x >> 2));
    }
};
}

int main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
    run();
    return 0;
}

// Opgave: K

class SockType {
public:
    ll left_count = 0;
    ll right_count = 0;
    ll any_count = 0;

    ll getMaxNonPairing() const {
        if (left_count > right_count)
            return left_count;
        if (right_count > left_count)
            return right_count;
        if (left_count == 0 && any_count > 0)
            return 1;
        if (left_count > 0)
            return left_count;
        return 0;
    }

    bool hasPairing() const {
        if (left_count > 0 && right_count > 0)
            return true;
        if (any_count > 0 && left_count + right_count + any_count > 1)
            return true;
        return false;
    }

    void addSocks(string fit, int amount) {
        if (fit == "right")
            right_count += amount;
        else if (fit == "left")
            left_count += amount;
        else if (fit == "any")
            any_count += amount;
    }
};

void run() {
    int socks = 0;
    cin >> socks;
    unordered_map <string, SockType> sockDrawer;
    REP(i, socks) {
        string sockType;
        string fit;
        int amount;
        cin >> sockType >> fit >> amount;
        sockDrawer[sockType].addSocks(fit, amount);
    }
    bool possibleConfigExists = false;
    for (const auto& sockType : sockDrawer) {
        if (sockType.second.hasPairing()) {
            possibleConfigExists = true;
            break;
        }
    }
    if (!possibleConfigExists) {
        std::cout << "impossible" << std::endl;
        return;
    }

    ll maxNumberOfPairlessSocks = 1;
    for (const auto& sockType : sockDrawer) {
        maxNumberOfPairlessSocks += sockType.second.getMaxNonPairing();
    }
    std::cout << maxNumberOfPairlessSocks << std::endl;
}