#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int n, m;
ll c[maxn];
int vis[maxn];
int col[maxn];
ll ans[maxn];
vector<int> cyc;
vector<ii> adj[maxn];
int root = 0, idx = -1;

vector<int> path;
void dfs(int par, int x, int d) {
	vis[x] = d;
	for(ii p : adj[x]) {
		int y = p.x;
		path.pb(p.y);
		if(vis[y] == 0) {
			col[y] = col[x] ^ 1;
			dfs(x, y, d + 1);
		} else {
			if(col[y] == col[x] && cyc.size() == 0) {
				for(int i = 0;i <= vis[x] - vis[y];i++)
					cyc.pb(path[path.size() - 1 - i]);
				root = y, idx = p.y;
			}
		}
		path.pop_back();
	}
}

void solve(int par, int x) {
	vis[x] = 1;
	for(ii p : adj[x]) {
		if(vis[p.x]) continue;
		if(p.y == idx) continue;
		solve(x, p.x);
		ans[p.y] = c[p.x], c[x] -= c[p.x];
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0;i < n;i++)
		scanf("%lld", c + i);
	for(int i = 0;i < m;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		adj[x].pb({y, i});
		adj[y].pb({x, i});
	}

	dfs(-1, 0, 1);
	memset(vis, 0, sizeof vis);
	solve(-1, root);
	if(idx == -1) {
		if(c[root] == 0) {
			printf("YES\n");
			for(int i = 0;i < m;i++)
				printf("%lld\n", ans[i]);
		} else printf("NO\n");
	} else {
		ll c_root = c[root] / 2;
		for(int i : cyc) 
			ans[i] += c_root, c_root *= -1;
		printf("YES\n");
		for(int i = 0;i < m;i++)
			printf("%lld\n", ans[i]);
	}
	return 0;
}
