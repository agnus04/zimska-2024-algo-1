#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1e5 + 5;
const ll inf = 1e18;

int n, K;
int A[maxn];
ll dp[25][maxn];
ll cnt[maxn];
int lo = 1, hi = 1;
ll c = 0;

ll cost(int x, int y) {
	while(x < lo) c += cnt[A[--lo]]++;
	while(x > lo) c -= --cnt[A[lo++]];
	while(y > hi) c += cnt[A[++hi]]++;
	while(y < hi) c -= --cnt[A[hi--]];
	return c;
}

void DnC(int i, int L, int R, int optL, int optR) {
	if(L > R) return;
	int j = (L + R) >> 1, opt = -1;
	
	for(int k = min(optR, j - 1);k >= optL;k--) {
		ll val = dp[i - 1][k] + cost(k + 1, j);
		if(dp[i][j] > val) dp[i][j] = val, opt = k;
	}
	DnC(i, L, j - 1, optL, opt);
	DnC(i, j + 1, R, opt, optR);
}

int main() {
	scanf("%d%d", &n, &K);
	for(int i = 1;i <= n;i++) 
		scanf("%d", A + i);
	
	cnt[A[1]]++;
	dp[1][0] = 0;
	for(int i = 1;i <= n;i++) 
		dp[1][i] = cost(1, i); 
		
	for(int i = 2;i <= K;i++) 
		for(int j = 0;j <= n;j++) 
			dp[i][j] = inf;
	
	for(int i = 2;i <= K;i++) 
		DnC(i, i, n, i - 1, n);
	printf("%lld\n", dp[K][n]);
	return 0;
}
