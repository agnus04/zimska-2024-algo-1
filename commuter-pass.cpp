#include<bits/stdc++.h>
 
#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> ii;
 
const int maxn = 2e5 + 5;
const ll inf = 1e18;
 
int n, m, s, t, u, v;
vector<pair<int, ll>> adj[maxn];
vector<int> G[maxn];
ll D[5][maxn];
ll mini[maxn];
int deg[maxn];
 
void get_dist(int X, int p) {
	vector<ll> dist(n, inf);
	dist[X] = 0;
	
	set<pair<ll, int>> q;
	q.insert({0, X});
	while(q.size()) {
		auto state = *q.begin();
		q.erase(state);
		int x = state.y;
		for(auto P : adj[x]) {
			int y = P.x;
			ll c = P.y;
			if(dist[y] == inf) {
				dist[y] = dist[x] + c;
				q.insert({dist[y], y});
			} else if(dist[x] + c < dist[y]) {
				q.erase({dist[y], y});
				dist[y] = dist[x] + c;
				q.insert({dist[y], y});
			}
		}
	}
	for(int i = 0;i < n;i++) 
		D[p][i] = dist[i];
}
 
vector<int> get_topo() {
	for(int i = 0;i < n;i++) 
		for(auto p : adj[i]) 
			if(D[0][t] == D[0][i] + p.y + D[1][p.x])
				G[i].pb(p.x), deg[p.x]++;
	
	queue<int> q;
	for(int i = 0;i < n;i++) 
		if(deg[i] == 0) q.push(i);
	
	vector<int> V;
	while(q.size()) {
		int x = q.front();
		q.pop(), V.pb(x);
		for(int y : G[x]) {
			deg[y]--;
			if(deg[y] == 0) 
				q.push(y);
		}
	}
	
	reverse(all(V));
	return V;
}
 
int main() {
	scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &u, &v);
	s--, t--, u--, v--;
	for(int i = 0;i < m;i++) {
		int x, y, c;
		scanf("%d%d%d", &x, &y, &c);
		x--, y--;
		adj[x].pb({y, c}), adj[y].pb({x, c});
	}
	
	get_dist(s, 0);
	get_dist(t, 1);
	get_dist(u, 2);
	get_dist(v, 3);
	
	vector<int> topo = get_topo();
	
	ll ans = inf;
	for(int x : topo) {
		mini[x] = D[3][x];
		for(int y : G[x]) 
			mini[x] = min(mini[x], mini[y]);
		
		ans = min(ans, D[2][x] + mini[x]);
	}
	
	for(int x : topo) {
		mini[x] = D[2][x];
		for(int y : G[x]) 
			mini[x] = min(mini[x], mini[y]);
		
		ans = min(ans, D[3][x] + mini[x]);
	}
	
	printf("%lld\n", ans);
	return 0;
}
