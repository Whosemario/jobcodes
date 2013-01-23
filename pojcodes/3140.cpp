#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 100003
#define _abs(x) ((x)<0?-(x):(x))

long long sum[SIZE];
int val[SIZE];
int col[SIZE];

struct Edge{
	int to;
	int next;
}edges[20000002];
int list[SIZE];
int index;

void insert(int from,int to){
	edges[index].to = to;
	edges[index].next = list[from];
	list[from] = index++;
	edges[index].to = from;
	edges[index].next = list[to];
	list[to] = index++;
}

void dfs(int now){
	col[now] = 1;
	sum[now] = val[now];
	for(int p = list[now];p!=-1;p=edges[p].next){
		if(col[edges[p].to]==0){
			dfs(edges[p].to);
			sum[now] += sum[edges[p].to];
		}
	}
}

int main()
{
	int N,M;
	int ca = 1;
	while(scanf("%d%d",&N,&M)&&N){
		for(int i=1;i<=N;i++)
			scanf("%d",&val[i]);
		memset(list,-1,sizeof(list));
		index = 0;
		for(int i=1;i<=M;i++){
		    int from,to;
			scanf("%d%d",&from,&to);
			insert(from,to);
		}
		if(N==1){
			printf("Case %d: %d\n",ca++,val[1]);
			continue;
		}
		memset(col,0,sizeof(col));
		dfs(1);

		long long res = -1;
		for(int i=2;i<=N;i++)
			if(res==-1 || _abs(sum[1]-sum[i]-sum[i]) < res)
				res = _abs(sum[1]-sum[i]-sum[i]);
		printf("Case %d: %lld\n",ca++,res);
	}
}