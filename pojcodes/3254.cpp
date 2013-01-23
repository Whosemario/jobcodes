#include<iostream>
#include<string.h>
using namespace std;

#define MOD 100000000

int dp[13][1<<12];
int mat[13];

bool isOk(int state, int N){
	for(int i=0;i<N-1;i++)
		if((state&(1<<i))!=0 && (state&(1<<(i+1)))!=0)
			return false;
	return true;
}

int main()
{
	int M,N;
	scanf("%d%d",&M,&N);
	memset(mat,0,sizeof(mat));
	if(M<N){
	   int tmp = M;
	   M = N;
	   N = tmp;
	   for(int i=0;i<N;i++)
		   for(int j=0;j<M;j++){
			   int s;
			   scanf("%d",&s);
			   if(s==1) mat[j] |= (1<<i);
		   }
	}
	else{
	   for(int i=0;i<M;i++)
		   for(int j=0;j<N;j++){
			   int s;
			   scanf("%d",&s);
			   if(s==1) mat[i] |= (1<<j);
		   }
	}

	memset(dp,0,sizeof(dp));

	for(int state = 0;state<(1<<N);state++)
		if((state&(~mat[0]))==0 && isOk(state,N))
			dp[0][state] = 1;

	for(int i=1;i<M;i++)
		for(int state = 0; state < (1<<N);state++){
		   if((state&(~mat[i]))==0 && isOk(state,N)){
		       for(int pre = 0; pre < (1<<N);pre++)
				   if((pre&state)==0){
				      dp[i][state] += dp[i-1][pre];
					  if(dp[i][state]>=MOD)
						  dp[i][state]-=MOD;
				   }
		   }
		}

	int res = 0;
	for(int state = 0; state < (1<<N); state ++){
	    res += dp[M-1][state];
		if(res >= MOD)
			res-=MOD;
	}

	printf("%d\n",res);

}