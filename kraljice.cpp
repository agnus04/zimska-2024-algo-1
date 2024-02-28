#include<bits/stdc++.h>
	
#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 1025;

int n;
int r[maxn];
int c[maxn];
int d1[maxn * 2]; 
int d2[maxn * 2];
vector<ii> ans;

int check(int x, int y) {
	return (r[x] + c[y] + d1[x + y] + d2[x - y + n] + 1) % 2;
}

void play(int x, int y) {
	ans.pb({x, y});
	r[x]++, c[y]++, d1[x + y]++, d2[x - y + n]++;
}

void resi4() {
	play(0, 1), play(1, 3), play(0, 2), play(1, 0);
	play(1, 1), play(2, 3), play(0, 3), play(2, 0);
	play(2, 1), play(2, 2), play(3, 0), play(3, 2);
	play(3, 1), play(3, 3);
}

void resi3() {
	play(1, 2), play(2, 0), play(1, 1);
	play(0, 0), play(2, 2), play(2, 1);
	play(0, 1), play(0, 2), play(1, 0);	
}
	
void rek(int n) {
	if(n <= 2) {play(0, 0);return;}
	if(n == 3) {resi3();return;}
	if(n == 4) {resi4();return;}
	rek(n - 2);
	
	for(int i = 0;i < n - 3;i++) {
		if(check(i, n - 1))
			play(i, n - 1), play(i, n - 2);
		else play(i, n - 2), play(i, n - 1);
		
		if(check(n - 1, i))
			play(n - 1, i), play(n - 2, i);
		else play(n - 2, i), play(n - 1, i);
	}
	
	if(n % 2 == 1) {
		play(n - 2, n - 1);
		play(n - 3, n - 2);
		play(n - 1, n - 2);
		play(n - 2, n - 2);
		play(n - 3, n - 1);
		play(n - 1, n - 3);
		play(n - 2, n - 3);
		play(n - 1, n - 1);	
	} else {
			play(n - 3, n - 1);	
			play(n - 3, n - 2);
			play(n - 2, n - 1);
			play(n - 2, n - 3);
			play(n - 1, n - 3);
			play(n - 2, n - 2);
			play(n - 1, n - 2);
			play(n - 1, n - 1);
		}
	}
	
	int main() {
		cin >> n;
		rek(n);
		printf("%d\n", (int)ans.size());
		for(ii p : ans)
			printf("%d %d\n", p.x + 1, p.y + 1);
		return 0;
	}
