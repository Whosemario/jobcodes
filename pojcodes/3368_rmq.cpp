#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

#define SIZE 100003
#define DELTA 100005

int val[SIZE];
int num[SIZE];
int index[SIZE*2];
int start[SIZE];
int N;
int mx[SIZE][16];
#define Max(x,y) ((x)>(y)?(x):(y))

void initRmq(){
	int len = (int)(log(N*1.0)/log(2.0));
	for(int i=1;i<=N;i++)
		mx[i][0]=num[i];
	for(int j=1;j<=len;j++)
		for(int i=N;i>=1;i--){
			mx[i][j]=mx[i][j-1];
			if(i+(1<<(j-1))<=N)
				mx[i][j]=Max(mx[i][j],mx[i+(1<<(j-1))][j-1]);
		}
}

int query(int l,int r){
	int lInd = index[val[l]];
	int rInd = index[val[r]];
	int lStart = start[lInd];
	int rStart = start[rInd];
	if(lInd==rInd){
		return r-l+1;
	}
	else if(lInd+1==rInd){
		return Max(rStart-l,r-rStart+1);
	}
	else{
		int ret = Max(start[lInd+1]-l,r-rStart+1);
		int m = (int)(log((rInd-1-lInd)*1.0)/log(2.0));
		int tmp = Max(mx[lInd+1][m],mx[rInd-(1<<m)][m]);
		return Max(ret,tmp);
	}
}

int main()
{
	while(scanf("%d",&N)&&N){
		int Q;
		scanf("%d",&Q);
		val[0]=0;
		index[0] = 0;
		int tmpN = 0;
		memset(num,0,sizeof(num));
		for(int i=1;i<=N;i++){
			scanf("%d",&val[i]);
			val[i]+=DELTA;
			if(val[i]!=val[i-1]){
				index[val[i]] = ++tmpN;
				start[tmpN]=i;
			}
			num[tmpN]++;
		}
		N = tmpN;
		initRmq();
		for(int i=1;i<=Q;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",query(l,r));
		}
	}
}