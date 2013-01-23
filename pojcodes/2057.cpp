#include<iostream>
#include<string.h>
using namespace std;

int children[1003][10];
char state[1003];
int leaves[1003];
int dp[1003];

int calcLeaves(int now){
	
	if(children[now][0]==0){
		leaves[now] = 1;
		return 1;
	}
	for(int i=1;i<=children[now][0];i++)
		leaves[now] += calcLeaves(children[now][i]);
	return leaves[now];
}

void childrenSort(int now){
	
	for(int i=1;i<=children[now][0];i++){
	   int ind = i;
	   for(int j=i+1;j<=children[now][0];j++)
		   if((dp[children[now][j]]+2)*leaves[children[now][ind]] < (dp[children[now][ind]]+2)*leaves[children[now][j]])
			   ind = j;
	   if(ind != i){
	      int tmp = children[now][i];
		  children[now][i]=children[now][ind];
		  children[now][ind] = tmp;
	   }
	}
}

int dfs(int now){
	if(state[now]=='Y' || children[now][0]==0){
		dp[now] = 0;
		if(children[now][0]!=0){
			for(int i=1;i<=children[now][0];i++)
				dfs(children[now][i]);
			childrenSort(now);
		}
	}
	else{
		dp[now]=0;
		for(int i=1;i<=children[now][0];i++)
			dp[now]+= dfs(children[now][i])+2;
		childrenSort(now);
	}
	return dp[now];
}

int res = 0;
void process(int now, int step){
	if(children[now][0]==0){
	   res += step;
	   return ;
	}
	int pre=0;
	for(int i=1;i<=children[now][0];i++){
		process(children[now][i],step+pre+1);
		pre += dp[children[now][i]]+2;
	}

}

int main()
{
	int N;
	while(scanf("%d",&N)&&N){
		memset(children,0,sizeof(children));
		for(int i=1;i<=N;i++){
		   int parent;
		   char sta;
		   scanf("%d %c",&parent,&sta);
		   if(parent != -1)
			children[parent][++children[parent][0]] = i;
		   state[i]=sta;
		}

		memset(leaves,0,sizeof(leaves));

		calcLeaves(1);

		memset(dp,0,sizeof(dp));

		dfs(1);

		res = 0;

		process(1,0);

		printf("%.4lf\n",res*1.0/leaves[1]);
	}
}