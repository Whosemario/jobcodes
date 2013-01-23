#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

int N,Q;
#define SIZE 50003
#define _max(x,y) ((x)>(y)?(x):(y))
#define _min(x,y) ((x)<(y)?(x):(y))
int val[SIZE];
int mx[SIZE][16];
int mn[SIZE][16];

void rmq_init()
{
	for(int i=1;i<=N;i++)
		mx[i][0]=mn[i][0]=val[i];
	int len = (int)(log(N*1.0)/log(2.0));

	for(int j=1;j<=len;j++)
		for(int i=1;i<=N;i++){
			mx[i][j] = mx[i][j-1];
			if(i+(1<<(j-1))<=N)
				mx[i][j]=_max(mx[i][j],mx[i+(1<<(j-1))][j-1]);
		}

	for(int j=1;j<=len;j++)
		for(int i=1;i<=N;i++){
			mn[i][j] = mn[i][j-1];
			if(i+(1<<(j-1))<=N)
				mn[i][j]=_min(mn[i][j],mn[i+(1<<(j-1))][j-1]);
		}
}

int query(int l,int r){
	int k = (int)(log((r-l+1)*1.0)/log(2.0));
	int a = _max(mx[l][k],mx[r-(1<<k)+1][k]);
	int b = _min(mn[l][k],mn[r-(1<<k)+1][k]);
	return a-b;
}

int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=1;i<=N;i++)
		scanf("%d",&val[i]);
	rmq_init();
	for(int i=1;i<=Q;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",query(l,r));
	}
	system("pause");
}