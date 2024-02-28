#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5;

int n, m, q;
int X[maxn];
int Y[maxn];
int opt[maxn];

struct UnionFind {
	int par[maxn];
	int sz[maxn];
	int col[maxn];
	int cnt;
	vector<pair<ii, int>> st;
	
	void init(int n) {
		cnt = 0, st.clear();
		for(int i = 0;i < n;i++)
			par[i] = i, sz[i] = 1, col[i] = 0;
	}
	
	int find(int x) {return (x == par[x]) ? x : find(par[x]);}
	int get_col(int x) {return (x == par[x]) ? 0 : col[x] ^ get_col(par[x]);}
	
	void merge(int x, int y) {
		int px = find(x), py = find(y);
		if(px == py) {
			if(get_col(x) == get_col(y)) cnt++;
			st.pb({{x, y}, 0});
		} else {
			if(sz[py] > sz[px]) 
				swap(x, y), swap(px, py);
			
			if(get_col(x) == get_col(y)) col[py] = 1;
			else col[py] = 0;
			sz[px] += sz[py];
			par[py] = px;
			st.pb({{px, py}, 1});
		}
	}
	
	void roll_back() {
		int x = st.back().x.x;
		int y = st.back().x.y;
		int type = st.back().y;
		st.pop_back();
		if(type) {
			sz[x] -= sz[y];
			par[y] = y, col[y] = 0;
		} else if(get_col(x) == get_col(y)) cnt--;
	}
	
	int check() {return cnt == 0;}
} DSU;

void solve(int l, int r, int optl, int optr) {
	if(l > r) return;
	int mid = (l + r) / 2;
	for(int i = l;i < mid;i++) DSU.merge(X[i], Y[i]);

	int idx = optr, num = 0;
	while(DSU.check() && mid < idx) {
		idx--, num++;
		DSU.merge(X[idx], Y[idx]);	
	}
	opt[mid] = idx;
	for(int i = 0;i < num;i++) DSU.roll_back();
	for(int i = l;i < mid;i++) DSU.roll_back();
	
	for(int i = 0;i < num;i++)
		DSU.merge(X[optr - i - 1], Y[optr - i - 1]);
	solve(l, mid - 1, optl, opt[mid]);
	for(int i = 0;i < num;i++) DSU.roll_back();
	
	for(int i = l;i <= mid;i++) DSU.merge(X[i], Y[i]);
	solve(mid + 1, r, opt[mid], optr);
	for(int i = l;i <= mid;i++) DSU.roll_back();
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0;i < m;i++)
		scanf("%d%d", X + i, Y + i), X[i]--, Y[i]--;
	DSU.init(n);
	solve(0, m - 1, 0, m);
	
	for(int i = 0;i < q;i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		printf("%s\n", (opt[l] > r) ? "YES" : "NO");	
	}
	return 0;
}

