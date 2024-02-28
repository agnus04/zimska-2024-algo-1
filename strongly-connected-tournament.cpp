#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2005;
const int MOD = 998244353;

int add(int x, int y) {x += y;if(x >= MOD) x -= MOD;return x;}
int sub(int x, int y) {x -= y;if(x < 0) x += MOD;return x;}
int mult(ll x, ll y) {return x * y % MOD;}
int pot(int n, int k) {
	if(k == 0) return 1;
	int ret = pot(n, k / 2);
	ret = mult(ret, ret);
	if(k & 1) ret = mult(ret, n);
	return ret;	
}
int divide(int x, int y) {return mult(x, pot(y, MOD - 2));}

int n;
int a, b, p;
int loss[maxn][maxn];
int strong[maxn];
int dp[maxn];

int main() {
	scanf("%d", &n);
	scanf("%d%d", &a, &b);
	p = divide(a, b);
	
	loss[0][0] = 1;
	for(int i = 1;i <= n;i++) {
		loss[i][0] = 1;
		for(int j = 1;j <= i;j++) {
			loss[i][j] = mult(pot(sub(1, p), j), loss[i - 1][j]);
			loss[i][j] = add(loss[i][j], mult(pot(p, i - j), loss[i - 1][j - 1])); 	
		}
	}	
	
	strong[1] = 1;
	for(int i = 2;i <= n;i++) {
		strong[i] = 1;
		for(int j = 1;j < i;j++)
			strong[i] = sub(strong[i], mult(strong[j], loss[i][j]));	
	}
	
	dp[0] = dp[1] = 0;
	for(int i = 2;i <= n;i++) {
		int x = sub(1, strong[i]);
		int y = 0;
		for(int j = 1;j < i;j++) {
			int s = mult(strong[j], loss[i][j]);
			s = mult(s, add(j * (i - j) + j * (j - 1) / 2, add(dp[j], dp[i - j])));
			y = add(y, s);
		}
		y = add(y, mult(strong[i], i * (i - 1) / 2));
		dp[i] = divide(y, x);
	}
	
	printf("%d\n", dp[n]);
	return 0;
}
 
