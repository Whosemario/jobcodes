#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 102

int mat[SIZE][SIZE];
int dp[SIZE];
int mx;
int best[SIZE];
int tmpBest[SIZE];
int stack[SIZE][SIZE];

void dfs(int N,int num,int step){
	if(num==0){
		if(step > mx){
			mx=step;
			for(int i=0;i<N;i++)
				best[i]=tmpBest[i];
		}
		return ;
	}

	for(int i=0;i<num;i++){
		int k = stack[step][i];
		if(step+N-k<=mx) return ;
		if(step+dp[k]<=mx) return ;
		int cnt = 0;
		tmpBest[k]=1;
		for(int j=i+1;j<num;j++)
			if(mat[k][stack[step][j]]){
			     stack[step+1][cnt++]=stack[step][j];
			}
		dfs(N,cnt,step+1);
		tmpBest[k]=0;
	}
}

void run(int N){
	memset(best,0,sizeof(best));
	memset(tmpBest,0,sizeof(tmpBest));
	mx =0;
	for(int i=N-1;i>=0;i--){
		int sz =0;
		tmpBest[i]=1;
		for(int j=i+1;j<N;j++)
			if(mat[i][j]) stack[1][sz++]=j;
		dfs(N,sz,1);
		tmpBest[i]=0;
		dp[i]=mx;
	}
}

int main()
{
	int M;
	scanf("%d",&M);
	while(M--){
		
		memset(mat,0,sizeof(mat));

		int N,K;
		scanf("%d%d",&N,&K);
		for(int i=0;i<K;i++){
			int to,from;
			scanf("%d%d",&to,&from);
			mat[to-1][from-1] = mat[from-1][to-1] = 1;
		}

		//reverse
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				if(i!=j)
					mat[i][j] ^= 1;

		run(N);
		printf("%d\n",mx);
		for(int i=0,j=0;i<N;i++)
			if(best[i]==1){
				if(j==0){
				    printf("%d",i+1);
				}
				else
					printf(" %d",i+1);
			    j++;
			}
		puts("");
	}
}