#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

int n, m, lim, ret;
int X[6], Y[6], T[6];
int M[10][10];
int mapa[10][10];
int mov[4][2]={{1, 0},{0, 1},{-1, 0},{0, -1}};

struct estado{
    int x;
    int y;
};
estado cola[102];
int inicio, fin;
int tiempo[10][10];
int cuantos;

void ampli(int a, int b, int p){
    estado hijo, act, ini;
    cuantos=p-1;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            tiempo[i][j]=-1;
        }
    }
    inicio=0; fin=0;
    ini.x=a;
    ini.y=b;
    tiempo[a][b]=1;
    cola[++fin]=ini;
    while(inicio!=fin){
        act=cola[++inicio];
        cuantos++;
        for(int i=0; i<4; i++){
            hijo.x=act.x+mov[i][0];
            hijo.y=act.y+mov[i][1];
            if(tiempo[hijo.x][hijo.y]==-1 && M[hijo.x][hijo.y]!=-1){
                tiempo[hijo.x][hijo.y]=1;
                cola[++fin]=hijo;
            }
        }
    }
}

int manhattan(int x, int y, int a, int b){
    return abs(x-a) + abs(y-b);
}

void busqueda(int x, int y, int p){
    if(x==1 && y==2){
        if(p==lim)
            ret++;
        return;
    }
    for(int i=1; i<=4; i++){
        if(x==X[i] && y==Y[i] && p!=T[i])
            return;
    }
    for(int i=1; i<=4; i++){
        if(p==T[i] && (x!=X[i] || y!=Y[i]))
            return;
    }
    for(int i=1; i<=4; i++){
        if(p < T[i] && manhattan(x, y, X[i], Y[i]) > (T[i] - p))
            return;
    }
    ampli(x, y, p);
    if(cuantos < lim)
        return;
    int unos=0, cual=0;
    for (int k=0; k<4; k++) {
        int r = x + mov[k][0], c = y+mov[k][1];
        if (M[r][c]==-1 || (r == 1 && c == 2)) continue;
        int vecinos = 0;
        for (int i=0; i<4; i++) {
            int a=r + mov[i][0], b=c + mov[i][1];
            if (M[a][b]==-1) continue;
            vecinos++;
        }
        if (vecinos == 0) return;
        if (vecinos == 1) {
            unos++;
            cual=k;
        }
    }
    if (unos > 1)
        return;
    if (unos == 1) {
        M[x+mov[cual][0]][y+mov[cual][1]]=-1;
        busqueda(x + mov[cual][0], y + mov[cual][1], p+1);
        M[x+mov[cual][0]][y+mov[cual][1]]=0;
        return;
    }
    for (int i=0; i<4; i++){
        if(M[x+mov[i][0]][y+mov[i][1]]==-1) continue;
        M[x+mov[i][0]][y+mov[i][1]]=-1;
        busqueda(x+mov[i][0], y+mov[i][1], p+1);
        M[x+mov[i][0]][y+mov[i][1]]=0;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    scanf("%d%d%d%d%d%d",&X[1],&Y[1],&X[2],&Y[2],&X[3],&Y[3]);

    X[1]++; Y[1]++; X[2]++; Y[2]++; X[3]++; Y[3]++;

    for(int i=1; i<=m; i++){
        M[0][i]=-1;
        M[n+1][i]=-1;
    }
    for(int i=1; i<=n; i++){
        M[i][0]=-1;
        M[i][m+1]=-1;
    }

    X[4]=1; Y[4]=2;
    mapa[X[1]][Y[1]]=1; mapa[X[2]][Y[2]]=2; mapa[X[3]][Y[3]]=3; mapa[1][2]=4;
    T[1]=(n*m)/4; T[2]=(n*m*2)/4; T[3]=(n*m*3)/4; T[4]=n*m; lim=n*m;

    M[1][1]=-1;
    busqueda(1, 1, 1);
    cout<<ret<<"\n";
    return 0;
}