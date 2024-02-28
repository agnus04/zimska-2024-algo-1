#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

int n;
set<int> s;

int ask(int x) {
	printf("? %d\n", x);
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;	
}

int print(int x) {
	for(int i = 29;i >= 0;i--) printf("%d", ((1 << i) & x) > 0);
	printf("\n");	
}

void DnC(int lo, int hi) {
	if(lo > hi) return;
	if(lo == hi) {
		s.insert(lo);
		return;
	}
	int mask = 0;
	for(int i = 29;i >= 0;i--) {
		mask += (1 << i) & hi;
		if((hi & (1 << i)) > 0 && (lo & (1 << i)) == 0) {
			int x = mask + ask(mask);
			DnC(x, hi);
			int y = mask - (1 << i) + ask(mask - 1) ^ ((1 << i) - 1);
			DnC(lo, y);
			return;
		}
	}
}

int main() {
	scanf("%d", &n);
	int a = ask(0), b = ask((1 << 30) - 1) ^ ((1 << 30) - 1);
	DnC(a, b);
	printf("! ");
	for(int i : s) printf("%d ", i);
	printf("\n");
	return 0;
}
