#include "glolib.h"
#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5;

int n;
vector<int> adj[maxn];
vector<int> v;
int ans[maxn];

void dfs(int x) {
	for(int y : adj[x]) dfs(y);
	if(adj[x].size() == 0) v.pb(x);
}

int main() {
	n = daj_n();
	for(int i = 1;i < n;i++) {
		int p = daj_przelozonego(i + 1) - 1;
		adj[p].pb(i);
	}
	dfs(0);

	ans[v[0]] = v[0];
	for(int i = 1;i < (int)v.size();i += 2)
		ans[v[i]] = v[i + 1], ans[v[i + 1]] = v[i];

	int x = v[0];
	while(1) {
		int y = ruch(x + 1) - 1;
		x = ans[y];
	}
	return 0;
}
