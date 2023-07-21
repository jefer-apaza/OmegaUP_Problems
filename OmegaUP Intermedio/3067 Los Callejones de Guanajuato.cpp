#include "callejones.h"

int N;
int E[1002][1002];

void eulerianPath(int node){
    for(int i = 0; i < N; i++)
        if(E[node][i]){
            E[node][i] = E[i][node] = 0;
            eulerianPath(i);
        }
    avanza(node);
}

void programa(int esquinas, int callejones, int matriz[][1000]) {
    N = esquinas;

	for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            E[i][j] = matriz[i][j];

	int O = 0, b = 0;
	
	for(int i = 0; i < N; i++){
        int degree = 0;
        for(int j = 0; j < N; j++)
        	degree += matriz[i][j];
        if( degree%2 ){
            O++;
        	b = i;
        }
	}
	
	if(O > 2){
        imposible();
        return;
	}
	
    eulerianPath(b);

}