#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 152

int dp[SIZE][SIZE];
int children[SIZE][SIZE];
int parent[SIZE];
int col[SIZE];
int P;

void dfs(int now){
	if(children[now][0]==0){
		dp[now][1]=0;
		return ;
	}
	dp[now][1]=0;
	for(int i=1;i<=children[now][0];i++){
		dfs(children[now][i]);
		for(int j=P;j>=1;j--){
			if(dp[now][j]!=-1){
			   for(int k =1;k<=P;k++)
				   if(dp[children[now][i]][k]!=-1 && j+k<=P &&
					   (dp[now][j+k]==-1 || dp[children[now][i]][k]+dp[now][j] < dp[now][j+k])){
				       dp[now][j+k] = dp[children[now][i]][k]+dp[now][j];
				   }
				dp[now][j]+=1;
			}
		}
	}
}

int main()
{
	int N;
	scanf("%d%d",&N,&P);

	memset(dp,-1,sizeof(dp));
	memset(children,0,sizeof(children));
	memset(parent,-1,sizeof(parent));
	memset(col,-1,sizeof(col));

	for(int i=1;i<N;i++){
		int p,c;
		scanf("%d%d",&p,&c);
		parent[c]=p;
		children[p][++children[p][0]] = c;
	}

	int root = 0;

	for(int i=1;i<=N;i++)
		if(parent[i]==-1){
			root = i;
			break;
		}

	dfs(root);

	int res = -1;
	for(int i=1;i<=N;i++)
		if(dp[i][P]!=-1){
		   int tmp = 0;
		   if(parent[i]==-1) tmp = dp[i][P];
		   else tmp = dp[i][P]+1;
		   if(res==-1 || tmp < res)
			   res = tmp;
		}

	printf("%d\n",res);

	system("pause");
}