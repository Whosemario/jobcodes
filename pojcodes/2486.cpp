/*
	dp[i][j][0]:在i节点还可以走j步，又走回i节点得到的最大苹果数
	dp[i][j][1]:在i节点还可以走j步，不一定走回i节点得到的最大苹果数
	
	dp[i][j][0]的转移方程很简单，dp[i][j][1]的转移方程有两个，注意体会第二
*/
#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 105

int children[SIZE][SIZE];
int val[SIZE];
int dp[SIZE][205][2];

int N,K;

#define _max(x,y) ((x)>(y)?(x):(y))

void dfs(int now,int parent){

	for(int i=0;i<=K;i++)
		dp[now][i][0]=dp[now][i][1]=val[now];

	if(children[now][0]!=0){
		for(int i=1;i<=children[now][0];i++){
			int child = children[now][i];
			if(child == parent) continue;
			dfs(child,now);

			for(int k=K;k>=0;k--)
				for(int j=0;j<=k;j++){
					//dp[now][k+2][0]
					dp[now][k+2][0] = _max(dp[now][k+2][0],dp[now][k-j][0]+dp[child][j][0]);
					//dp[now][k+1][1]
					dp[now][k+1][1] = _max(dp[now][k+1][1],dp[now][k-j][0]+dp[child][j][1]);
					//dp[now][k+2][1]
					dp[now][k+2][1] = _max(dp[now][k+2][1],dp[now][k-j][1]+dp[child][j][0]);
				}
		}
	}

}

int main()
{
	while(scanf("%d%d",&N,&K)!=EOF){
		for(int i=1;i<=N;i++)
			scanf("%d",&val[i]);
		memset(children,0,sizeof(children));
		for(int i=1;i<N;i++){
		    int from,to;
			scanf("%d%d",&from,&to);
			children[from][++children[from][0]] = to;
			children[to][++children[to][0]] = from;
		}

		memset(dp,0,sizeof(dp));

		dfs(1,-1);

		printf("%d\n",dp[1][K][1]);
	}
}