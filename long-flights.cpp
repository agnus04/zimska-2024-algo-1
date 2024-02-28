#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5, maxd = 200;

int n, m, p;
vector<int> adj[maxn];
int has[maxn];
int dist[maxd][maxn];

void bfs(int x, int idx) {
	for(int i = 0;i < n;i++) 
		dist[idx][i] = n;
	dist[idx][x] = 0;
	queue<int> q;
	q.push(x);
	
	while(q.size()) {
		x = q.front();q.pop();
		for(int y : adj[x]) {
			if(dist[idx][x] + 1 < dist[idx][y]) {
				dist[idx][y] = dist[idx][x] + 1;
				q.push(y);
			}
		}
	}
}

int main() {
	mt19937 rng(39465329);
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 0;i < m;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		adj[x].pb(y), adj[y].pb(x);
	}
	
	vector<int> v;
	for(int i = 0;i < n;i++) v.pb(i);
	shuffle(all(v), rng);
	int N = min(maxd, n);
	for(int i = 0;i < N;i++) bfs(v[i], i);
	
	for(int i = 0;i < p;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		int ans = n;
		for(int j = 0;j < N;j++) 
			ans = min(ans, dist[j][x] + dist[j][y]);
		printf("%d\n", ans);
	}
	return 0;
}
