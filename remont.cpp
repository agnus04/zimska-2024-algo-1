#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e6 + 5;

int n, k, C = 1, N;
vector<int> adj[2][maxn];
int vis[maxn];

void add_or(int x, int y) {
	adj[0][y ^ 1].pb(x);
	adj[0][x ^ 1].pb(y);
	adj[1][x].pb(y ^ 1);
	adj[1][y].pb(x ^ 1);
}

void add_impl(int x, int y, int f) {
	adj[0][x].pb(y);
	adj[1][y].pb(x);
	if(f) {
		adj[0][y ^ 1].pb(x ^ 1);
		adj[1][x ^ 1].pb(y ^ 1);
	}
}

vector<int> topo;
void dfs(int x, int f) {
	if(vis[x]) return;
	vis[x] = C;
	for(int y : adj[f][x]) dfs(y, f);
	if(f == 0) topo.pb(x);
}

void build(vector<int> &v) {
	int m = (int)v.size();
	if(m == 1) return;
	
	add_impl(2 * v[0], 2 * N, 1);
	for(int i = 1;i < m;i++) {
		add_impl(2 * v[i], 2 * (N + i), 1);
		add_impl(2 * (N + i - 1), 2 * (N + i), 1);
	}
	
	add_impl(2 * v[m - 1], 2 * (N + m + m - 1), 1);
	for(int i = m - 2;i >= 0;i--) {
		add_impl(2 * v[i], 2 * (N + m + i), 1);
		add_impl(2 * (N + m + i + 1), 2 * (N + m + i), 1);
	}
	
	for(int i = 0;i < m - 1;i++) 
		add_impl(2 * (N + i), 2 * (N + m + i + 1) + 1, 0);
	for(int i = m - 1;i > 0;i--) 
		add_impl(2 * (N + m + i), 2 * (N + i - 1) + 1, 0);
	
	N += 2 * m;
}

void cleanup() {
	C = 1, topo.clear();
	for(int i = 0;i < 2 * N;i++) 
		adj[0][i].clear(), adj[1][i].clear(), vis[i] = 0;
}

void solve() {
	scanf("%d%d", &n, &k);
	map<ii, vector<int>> M;
	vector<int> a(n, 0);
	for(int &i : a) scanf("%d", &i);
	
	add_or(0, 0);
	for(int i = 0;i < n - 2;i++)
		add_or(2 * i, 2 * (i + 1));
	add_or(2 * (n - 2), 2 * (n - 2));
	
	for(int i = 0;i < n - 1;i++) 
		M[{a[i], a[i + 1]}].pb(i);
	
	N = n - 1;
	for(auto p : M) build(p.y);
	
	for(int i = 0;i < 2 * N;i++) dfs(i, 0);
	memset(vis, 0, sizeof vis);
	reverse(all(topo));
	for(int i : topo) {
		if(vis[i]) continue;
		C++, dfs(i, 1);	
	}
	
	int flag = 1;
	for(int i = 0;i < N;i++) 
		if(vis[2 * i] == vis[2 * i + 1]) flag = 0;
	printf("%s\n", flag ? "TAK" : "NIE");
	cleanup();
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) solve();
	return 0;
}
