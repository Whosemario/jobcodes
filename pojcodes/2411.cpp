#include<iostream>
#include<string.h>
using namespace std;

int H,W;

long long dp[12][1<<11];
char num[1<<11];
int state[1<<11][1<<11];

void dfs(int now, int res , int ind){
	if(ind==W){
	    state[now][++state[now][0]] = res;
		return ;
	}
	if(now&(1<<ind)){
		if(ind!=W-1 && (now&(1<<(ind+1)))){
		   // horizontal
		   dfs(now,res,ind+2);
		}
		// veritcal
	    dfs(now,res^(1<<ind),ind+1);
	}
	else
		dfs(now,res,ind+1);
}

long long process(int h,int now){
	if(h==1)
		return num[now];
	if(now==0)
		return process(h-1,(1<<W)-1);
	if(dp[h][now]!=-1)
		return dp[h][now];
	long long ret = 0;
	
	for(int i=1;i<=state[now][0];i++){
	    ret += process(h-1,state[now][i]);
	}

	dp[h][now]=ret;

	return ret;
}

int main()
{
	while(scanf("%d%d",&H,&W) && H){
		if(W > H){
		   int tmp = H;
		   H = W;
		   W = tmp;
		}

		memset(num,0,sizeof(num));

		for(int s=0;s<(1<<W);s++){
			int flag = 1;
			for(int i=0;i<W;)
				if((1<<i)&s){
					if((1<<(i+1))&s) i+=2;
					else{flag=0;break;}
				}
				else ++i;
			num[s]=flag;
		}

		for(int s = 1;s<(1<<W);s++){
		    state[s][0]=0;
			dfs(s,(1<<W)-1,0);
		}

		memset(dp,-1,sizeof(dp));

		long long res = process(H,(1<<W)-1);

		printf("%lld\n",res);

	}
}