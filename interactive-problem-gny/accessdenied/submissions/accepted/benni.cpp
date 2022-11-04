#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(auto i = (a); i < (b); i++)
#define pb push_back
#define fs first
#define sc second
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const double EPS = 1e-9;


string pass = "Benni5";
// return -1 if correct

int CheckPassword(string pwd1, string pwd2) {
    int tm = 0;
    tm += 1;
    if (pwd1.size() != pwd2.size()) {
        return tm;
    }

    for (int i = 0; i < pwd1.size(); i++) {
        tm += 1;
        if (pwd1[i] != pwd2[i]) {
            return tm;
        }
    }
    return -1;
}
int ask(string s) {
    cout << s << endl;
    /*int val2 = CheckPassword(s,pass);
    cout << " val get : " << val2 << endl;
    return val2;*/
    string a,b;
    cin >> a >> b;
    if(b == "GRANTED") return -1;
    string c,d;
    cin >> c >> d;
    c.erase(c.begin());
    int val = stoi(c);
    return val;
}

string alp = "";

int main() {
    cin.sync_with_stdio(false);
    rep(i,0,26) alp += char('a'+i);
    rep(i,0,26) alp += char('A'+i);
    rep(i,0,10) alp += char('0'+i);
    // find length
    vi VAL;
    rep(i,0,20) {
        string s = "";
        rep(z,0,i+1) s+= "i";
        int val = ask(s);
        if(val == -1) {
            return 0;
        }
        VAL.pb(val);
    }
    int length = 0;
    rep(i,0,20) if(VAL[i] > VAL[length]) {
        length = i;
    }

    length++;
    string got = "";
    rep(i,0,length) got += "i";
    rep(i,0,length) {
        vi VAL2;
        for(auto l : alp) {
            string  kk = got;
            kk[i] = l;
            int val = ask(kk);
            if(val == -1) return 0;
            VAL2.pb(val);
        }
        int mx = 0;
        rep(j,0,alp.size()) {
            if(VAL2[mx] < VAL2[j]) mx = j;
        }
        got[i] = alp[mx];
    }
}

