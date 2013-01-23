/*关键在状态的数量，不会有1<<m那么多，即使m=10，最终的状态也就不超过50个*/
#include<iostream>
#include<string.h>
using namespace std;

int N,M;

int mat[102];
int states[100]; 

int dp[102][100][100];

bool isOk(int sta){
	for(int i=0;i<M;i++)
		if(sta&(1<<i)){
			if(i+1<M && (sta&(1<<(i+1))))
				return false;
			if(i+2<M && (sta&(1<<(i+2))))
				return false;
		}

	return true;
}

int dfs(int pre,int now,int step){
	if(step==1){
	    int ret = 0;
		for(int i=0;i<M;i++)
			if(states[pre]&(1<<i))
				ret++;
	    return ret;
	}
	if(dp[step][pre][now]!=-1)
		return dp[step][pre][now];
	int ret = 0;
	int num = 0;
	for(int i=0;i<M;i++)
		if(states[pre]&(1<<i)) num++; 
	int ban = states[pre] | states[now];
	for(int i=1;i<=states[0];i++){
	   if((ban&states[i])==0 && (states[i]&(~mat[step-2]))==0){
	        int tmp = num + dfs(now,i,step-1);
			if(tmp > ret) ret = tmp;
	   }
	}
	dp[step][pre][now] = ret;
	return ret;
}

int main()
{
	scanf("%d%d",&N,&M);

	char input[12];

	mat[0] = 0; // all of them are H
	for(int i=1;i<=N;i++){
	    scanf("%s",input);
		mat[i]=0;
		for(int j=0;j<M;j++)
			if(input[j]=='P')
				mat[i] |= (1<<j);
	}

	states[0] = 0;
	for(int s=0;s<(1<<M);s++)
		if(isOk(s))
			states[++states[0]] = s;

	memset(dp,-1,sizeof(dp));

	int res = 0;

	for(int i=1;i<=states[0];i++)
		for(int j=1;j<=states[0];j++)
			if((states[i]&states[j])==0){
				if((states[i]&(~mat[N]))==0 && (states[j]&(~mat[N-1]))==0){
				   int tmp = dfs(i,j,N);
				   if(tmp > res) res = tmp;
				}
			}

	printf("%d\n",res);

}