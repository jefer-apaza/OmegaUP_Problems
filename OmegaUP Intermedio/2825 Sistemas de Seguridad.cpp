#include <iostream>
#include <algorithm>
#include <vector>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

int n, r, c, p;
vector<int> E[102];
int R[102], B[102], S[102], Br[102];
int DP[102][102], vis[102][102];

void DFSpreprocess( int node ){
	
	S[node] = E[node].size() ? E[node][0] : 0;
	for( int i = 0; i < E[node].size(); i++ ){
		DFSpreprocess( E[node][i] );
		R[node] += R[ E[node][i] ];
		B[node] += B[ E[node][i] ];
		Br[ E[node][i] ] = i < E[node].size() - 1 ? E[node][i + 1] : 0;
	}
	
}

int DFSdp( int i, int r ){
	
	if( r <= 0 )
		return 0;
	
	if( i == 0 )
		return 10000;
	
	if( !vis[i][r] ){
		vis[i][r] = 1;
		DP[i][r] = DFSdp( Br[i], r - R[i] ) + B[i];
		for( int j = 0; j <= r; j++ )
			DP[i][r] = min( DP[i][r], DFSdp( S[i], j ) + DFSdp( Br[i], r - j ) );
	}
	return DP[i][r];
	
}

int main(){
	
	optimizar_io
	cin >> n >> r;
	for( int i = 1; i <= n; i++ ){
		cin >> c;
		if( c == 1 )
			B[i]++;
		else
			R[i]++;
	}
	
	for( int i = 2; i <= n; i++ ){
		cin >> p;
		E[p].push_back( i );
	}
	
	DFSpreprocess( 1 );
	r = R[1] - r;
	cout << DFSdp( 1, r ) << "\n";
	
	return 0;
	
}