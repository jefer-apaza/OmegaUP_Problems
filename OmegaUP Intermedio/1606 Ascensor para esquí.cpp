#include <stdio.h>
#include <algorithm>
#define inf -1500000000
 
using namespace std;
 
double H[5002];
int n, k;
int DP[5002];
 
double m(int i, int j){
	double dify=H[i]-H[j];
	double difx=((i)-(j));
	return dify/difx;
} 
 
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%lf",&H[i]);
	}
	double mayor, pend;
	for(int i=n; i>=1; i--){
		mayor= -1500000000;
		if(i<n)
			DP[i]=10000;
		for(int j=i+1; j<=n && j<=i+k; j++){
			pend=m(j, i);
			if(!(pend<mayor)){
				DP[i]=min(DP[j], DP[i]);
				mayor=pend;
			}
		}
		DP[i]++;
	}
	printf("%d\n",DP[1]);
	return 0;
}