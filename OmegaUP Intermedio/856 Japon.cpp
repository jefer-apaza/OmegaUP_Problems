#include <iostream>
#include <algorithm>
#include <stdio.h>
 
using namespace std;
 
int n, m, k, t;
struct linea{
    int x;
    int y;
};
linea L[2000002];
bool f(linea a, linea b){
    if(a.x>b.x)
        return true;
    if(b.x>a.x)
        return false;
    return a.y>b.y;
}
 
int BIT[100002];
void inserta(int p){
    for(; p<=n; p+=(p&-p))
        BIT[p]++;
}
 
long long int query(int p){
    long long int ret=0;
    for(; p; p-=(p&-p))
        ret+=BIT[p];
    return ret;
}
 
int main()
{
    scanf("%d",&t);
    for(int c=1; c<=t; c++){
        scanf("%d%d%d",&m,&n,&k);
        for(int i=1; i<=k; i++){
            scanf("%d%d",&L[i].x,&L[i].y);
        }
        sort(L+1, L+k+1, f);
        long long int resp=0;
        for(int i=1; i<=k; i++){
            inserta(L[i].y);
            resp+=query(L[i].y-1);
        }
        for(int i=1; i<=n; i++){
            BIT[i]=0;
        }
        printf("Test case %d: %lld\n",c,resp);
    }
    return 0;
}