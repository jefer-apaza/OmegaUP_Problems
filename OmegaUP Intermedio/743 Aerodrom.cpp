#include <iostream>
#include <stdio.h>
 
using namespace std;
 
long long int l=1;
long long int inf=(l<<60);
long long int T[1000002];
long long int n, m;
 
long long int cuantos(long long int k){
    long long int ret=0;
    for(int i=1; i<=n; i++)
        ret+=(k/T[i]);
    return ret;
}
 
long long int binaria(){
    long long int ini=1, fin=inf, mitad;
    while(ini!=fin){
        mitad=(ini+fin)/2;
        if(cuantos(mitad)>=m)
            fin=mitad;
        else
            ini=mitad+1;
    }
    return ini;
}
 
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%lld",&T[i]);
    }
    printf("%lld\n",binaria());
    return 0;
}