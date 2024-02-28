#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;


int main() {
	int n;
	cin >> n;
	if(n == 1) {
		printf("1\n1 1\n");
		return 0;
	}
	
	cout << (2 * n + 1) / 3 << "\n";
	if(n % 3 != 2) 
		cout << n << " " << n << "\n", n--;
	if(n % 3 != 2) 
		cout << n << " " << n << "\n", n--;
	
	int k = (2 * n + 1) / 3;
	int k1 = k / 2;
	int k2 = k - k1;
	for(int i = 0;i < k2;i++)
		cout << i + 1 << " " << k2 - i << "\n";
	for(int i = 0;i < k1;i++) 
		cout << n - k1 + 1 + i << " " << n - i << "\n";
	return 0;
}
 
