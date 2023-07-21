#include <stdio.h>
#include <iostream>
 
using namespace std;
 
long long int n, m;
long long int H[1000002];
int maximo;
 
long long int wood(long long int height){
	long long int ret=0;
	for(int i=1; i<=n; i++){
		if(H[i]>height)
			ret+=H[i]-height;
	}
	return ret;
}
 
int binaria(int ini, int fin){
	long long int mitad=((ini)+(fin));
	mitad/=2;
	mitad++;
	if(ini==fin)
		return ini;
	if(wood(mitad)>=m)
		return binaria(mitad, fin);
	return binaria(ini, mitad-1);
}
 
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%lld",&H[i]);
		if(H[i]>maximo)
			maximo=H[i];
	}
	printf("%d\n",binaria(0, maximo+1));
	return 0;
}