#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

struct seg {
	int sz, pot;
	vector<ii> T;
	vector<ii> nxt;
	
	void init() {
		sz = 1, pot = (1 << 20);
		T.pb({-1, 0});
		nxt.pb({-1, -1});
	}
	
	ii merge(ii A, ii B) {
		ii ret;
		ret.x = max(A.x, B.x);
		ret.y = A.y + B.y;
		return ret;	
	}
	
	void expand(int x) {
		if(nxt[x].x == -1) {
			nxt[x].x = sz++;
			T.pb({-1, 0}), nxt.pb({-1, -1});	
		}
		if(nxt[x].y == -1) {
			nxt[x].y = sz++;
			T.pb({-1, 0}), nxt.pb({-1, -1});	
		}	
	}
	
	void update(int x, int lo, int hi, int X, int v) {
		if(X < lo || X > hi) return;
		if(lo == hi) {
			T[x].x = v, T[x].y++;
			return;
		}
		int mid = (lo + hi) / 2;
		expand(x);
		update(nxt[x].x, lo, mid, X, v);
		update(nxt[x].y, mid + 1, hi, X, v);
		T[x] = merge(T[nxt[x].x], T[nxt[x].y]);
	}
	
	ii query(int x, int lo, int hi, int a, int b) {
		if(hi < a || b < lo) return {-1, 0};
		if(a <= lo && hi <= b) return T[x];
		int mid = (lo + hi) / 2;
		expand(x);
		ii L = query(nxt[x].x, lo, mid, a, b);
		ii R = query(nxt[x].y, mid + 1, hi, a, b);
		return merge(L, R);
	}
	
	ii get(int lo, int hi) {
		return query(0, 0, pot - 1, lo, hi);	
	}
	
	void add(int x, int v) {
		update(0, 0, pot - 1, x, v);	
	}
};

int n, k;

ll F(vector<int> a) {
	ll ret = 0;
	vector<int> dp(n, 0);
	seg S;
	S.init();
	for(int i = 0;i < n;i++) {
		ii p = S.get(a[i] + 1, a[i] + k);
		int j = p.x;
		if(j != -1) dp[i] = dp[j] + S.get(a[i] + 1, a[j]).y;
		ret += (ll)dp[i];
		S.add(a[i], i);
	}
	return ret;
}

void solve() {
	scanf("%d%d", &n, &k);
	vector<int> a(n, 0);
	for(int &i : a) scanf("%d", &i);
	
	map<int, int> cnt;
	for(int i : a) cnt[i]++;
	
	ll ans = 0;
	for(auto p : cnt) 
		ans += (ll)p.y * (p.y + 1) / 2;
	ans += F(a);
	reverse(all(a));
	ans += F(a);
	printf("%lld\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) solve();
	return 0;
}
