#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int n = 100;
int mat[n][n];
vector<int> know;
map<vector<int>, int> G;

mt19937 rng(39465329);

int ask(int x, int y, int z) {
	printf("? %d %d %d\n", x + 1, y + 1, z + 1);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;
}	

int idx(int x, int y) {
	return x * 5 + y - (x + 1) * (x + 2) / 2;	
}

void prep() {
	for(int i = 0;i < (1 << 10);i++) {
		vector<int> ans;
		for(int a = 0;a < 5;a++)
			for(int b = a + 1;b < 5;b++) {
				vector<int> v;
				for(int j = 0;j < 5;j++) 
					if(j != a && j != b) v.pb(j);
				int cnt = 0;
				int p1 = idx(v[0], v[1]);
				int p2 = idx(v[0], v[2]);
				int p3 = idx(v[1], v[2]);
				cnt += (i & (1 << p1)) > 0;
				cnt += (i & (1 << p2)) > 0;
				cnt += (i & (1 << p3)) > 0;
				ans.pb(cnt);
			}
		G[ans] = i;
	}
}

void add(int x, vector<int> v) {
	int m = v.size();
	if(m == 0) return;
	if(m == 1) {
		if(know.size()) {
			int y = know.back();
			mat[x][v[0]] = mat[v[0]][x] = ask(x, y, v[0]) - mat[x][y] - mat[y][v[0]];
		} else {
			int y = 0, z = 1;
			if(v[0] == 0) y = 1, z = 2;
			if(v[0] == 1) z = 2;
			int a = ask(x, y, z) - mat[y][z];
			int b = ask(x, y, v[0]) - mat[y][v[0]];
			int c = ask(x, z, v[0]) - mat[z][v[0]];
			mat[x][v[0]] = mat[v[0]][x] = (b + c - a) / 2;
			know.pb(v[0]);	
		}
		return;
	}
	vector<int> new_v, idx;
	for(int i = 1;i < m;i += 2) {
		int cnt = ask(x, v[i - 1], v[i]) - mat[v[i - 1]][v[i]];
		if(cnt == 0) {
			know.pb(v[i]), know.pb(v[i - 1]);
			mat[x][v[i]] = mat[v[i]][x] = 0;
			mat[x][v[i - 1]] = mat[v[i - 1]][x] = 0;
		}
		if(cnt == 2) {
			know.pb(v[i]), know.pb(v[i - 1]);
			mat[x][v[i]] = mat[v[i]][x] = 1;
			mat[x][v[i - 1]] = mat[v[i - 1]][x] = 1;
		}
		if(cnt == 1)
			new_v.pb(v[i]), idx.pb(i);
	}
	
	add(x, new_v);
	for(int i : idx) {
		know.pb(v[i - 1]);
		mat[x][v[i - 1]] = mat[v[i - 1]][x] = !mat[x][v[i]];
	}
	
	if(m & 1) {
		int z = v.back();
		int y = know.back();
		mat[x][z] = mat[z][x] = ask(x, y, z) - mat[x][y] - mat[y][z];	
	}
}

int main() {
	prep();
	vector<int> ans;
	for(int i = 0;i < 5;i++)
		for(int j = i + 1;j < 5;j++) {
			vector<int> v;
			for(int k = 0;k < 5;k++) 
				if(k != i && k != j) v.pb(k);	
			ans.pb(ask(v[0], v[1], v[2]));
		}
	int mask = G[ans];
	for(int i = 0;i < 5;i++)
		for(int j = i + 1;j < 5;j++)
			if(mask & (1 << idx(i, j))) 
				mat[i][j] = mat[j][i] = 1;
	
	for(int i = 5;i < n;i++) {
		vector<int> v;
		for(int j = 0;j < i;j++) v.pb(j);
		shuffle(all(v), rng);
		know.clear();
		add(i, v);
	}
	printf("!\n");
	for(int i = 0;i < n;i++, printf("\n"))
		for(int j = 0;j < n;j++) printf("%d", mat[i][j]);
	return 0;
}

