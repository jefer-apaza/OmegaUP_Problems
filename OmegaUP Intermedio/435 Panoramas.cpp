#include <iostream>
#include <vector>
#include <algorithm>
#define optimizar_io ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;

int n, m, r, a, b;
int I[10002];
vector<int> E[10002], T[10002];
bool vis[10002];
int c, wP, tC;
int C[10002], P[20002], inCycle[10002];
int Tr[10002];

int buildTree( int node, int parent ){
    int ret = 0;
    for( int i = 0; i < E[node].size(); i++ )
        if( !inCycle[ E[node][i] ] && E[node][i] != parent ){
            T[node].push_back( E[node][i] );
            if( buildTree( E[node][i], node ) )
                ret = 1;
        }
    if( I[node] )
        ret = 1;
    return ret;
}

void getCycle( int a, int b ){

    if( Tr[b] == a ){
        c = 2;
        C[1] = a; C[2] = b;
        inCycle[a] = inCycle[b] = 1;
    } else {
        while( a != b ){
            C[++c] = a;
            inCycle[a] = 1;
            a = Tr[a];
        }
        C[++c] = a;
        inCycle[a] = 1;
        a = Tr[a];
    }

    for( int i = 1; i <= c; i++ ){
        P[i] = buildTree( C[i], 0 );
        wP += P[i];
    }
    tC = 1;

}

void DFS( int node ){

    vis[node] = 1;
    for( int i = 0; i < E[node].size(); i++ ){
        if( !vis[ E[node][i] ] ){
            Tr[ E[node][i] ] = node;
            DFS( E[node][i] );
        } else {
            if( E[node][i] != Tr[node] && !tC )
                getCycle( node, E[node][i] );
        }
    }

}

int minTree( int node ){
    int ret = 0;
    for( int i = 0; i < T[node].size(); i++ )
        ret += minTree( T[node][i] );
    ret += ( ret || I[node] ) ? 1 : 0;
    return ret;
}

int main()
{

    optimizar_io
    cin >> n >> m;

    if( m == 0 ){
        cout << "0\n";
        return 0;
    }

    for( int i = 1; i <= m; i++ ){
        cin >> r;
        I[r]++;
    }
    for( int i = 1; i <= n; i++ ){
        cin >> a >> b;
        E[a].push_back(b);
        E[b].push_back(a);
    }
    DFS(1);

    int ans = 0;
    if( wP > 1 ){
        for( int i = 1; i <= c; i++ ){
            ans += P[i] ? minTree( C[i] ) : 0;
            P[i+c] = P[i];
        }
        int maxD = 0, i = 0, acu = 0;
        while( !P[i] )
            i++;
        while( i <= 2 * c ){
            if( P[i] ){
                maxD = max( maxD, acu );
                acu = 0;
            } else {
                acu++;
            }
            i++;
        }
        ans += c - maxD - wP;
    } else {
        ans = minTree( r );
    }
    cout << ans << "\n";

    return 0;

}