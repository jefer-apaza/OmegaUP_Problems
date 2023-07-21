#include <iostream>
#include <algorithm>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

int n, d;
int A[100002];

int main(){
	
	optimizar_io
	cin >> n >> d;
	for( int i = 1; i <= n; i++ )
		cin >> A[i];
	sort( A + 1, A + n + 1 );
	
	int ans = 0, p;
	for( int i = 1; i <= n; i++ ){
		p = upper_bound( A + 1, A + n + 1, A[i] + d ) - A;
		p = min( n, p );
		if( A[p] > A[i] + d )
			p--;
		ans = max( ans, p - i + 1 );
	}
	cout << ans << "\n";
	
	return 0;
	
}