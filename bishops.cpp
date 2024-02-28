#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;

int n, m, flag;
vector<ii> ans;
map<int, int> d1, d2;

void add(int x, int y) {
	ans.pb({x, y});
	d1[x + y]++, d2[x - y]++;	
}

int main() {
	scanf("%d%d", &n, &m);
	if(n > m) swap(m, n), flag = 1;
	
	if(n == m) {
		for(int i = 0;i < n;i++) ans.pb({0, i});
		for(int i = 1;i < n - 1;i++) ans.pb({n - 1, i});
	} else {
		for(int i = 0;i < n;i++)
			add(i, 0), add(i, m - 1);
		
		vector<int> v10, v20, v11, v21;
		for(int i = 0;i < n + m - 1;i++)
			if(d1[i] == 0) {
				if(i & 1) v11.pb(i);
				else v10.pb(i);	
			}
	
		for(int i = -m + 1;i < n;i++)
			if(d2[i] == 0) {
				if(i & 1) v21.pb(i);
				else v20.pb(i);	
			}
		
		int N = min(v10.size(), v20.size());
		int M = min(v11.size(), v21.size());
		reverse(all(v20));
		reverse(all(v21));
		for(int i = 0;i < N;i++) 
			ans.pb({(v10[i] + v20[i]) / 2, (v10[i] - v20[i]) / 2});
		for(int i = 0;i < M;i++) 
			ans.pb({(v11[i] + v21[i]) / 2, (v11[i] - v21[i]) / 2});
	}
	
	printf("%d\n", (int)ans.size());
	for(ii p : ans)
		if(flag == 0) printf("%d %d\n", p.x + 1, p.y + 1);
		else printf("%d %d\n", p.y + 1, p.x + 1);
	return 0;
}
