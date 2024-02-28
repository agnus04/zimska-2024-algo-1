#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int MOD = 1e9 + 7;
const int maxn = 55, maxl = 1e4 + 5;

int add(int x, int y) {x += y;if(x >= MOD) x -= MOD;return x;}
int mult(ll x, ll y) {return x * y % MOD;}

int n, l;
int r[maxn];
int dp[2][maxn][maxl];
int choose[maxl + maxn][maxn];

int main() {
	scanf("%d%d", &n, &l);
	for(int i = 1;i <= n;i++)
		scanf("%d", r + i);
	
	sort(r + 1, r + n + 1);
	dp[0][0][0] = 1;
	for(int i = 1;i <= n;i++) {
		dp[i & 1][0][0] = 0;
		for(int j = 1;j <= i;j++) {
			for(int d = 1;d <= l;d++) {
				dp[i & 1][j][d] = dp[!(i & 1)][j - 1][d - 1];
				if(d >= r[i]) dp[i & 1][j][d] = add(dp[i & 1][j][d], mult(dp[!(i & 1)][j][d - r[i]], 2 * j));
				if(d >= 2 * r[i] - 1) dp[i & 1][j][d] = add(dp[i & 1][j][d], mult(dp[!(i & 1)][j + 1][d - 2 * r[i] + 1], j * (j + 1)));
			}
		}
	}
	
	for(int i = 0;i <= l + n;i++) 
		choose[i][0] = 1;
	for(int i = 1;i <= l + n;i++)
		for(int j = 1;j <= min(n, i);j++)
			choose[i][j] = add(choose[i - 1][j], choose[i - 1][j - 1]);
	
	int ans = 0;
	for(int d = 1;d <= l;d++)
		ans = add(ans, mult(dp[n & 1][1][d], choose[l - d + n][n]));
	printf("%d\n", ans);
	return 0;
}

