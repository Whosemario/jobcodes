#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 100

int mat[SIZE][SIZE];  /*Õºæÿ’Û*/

int match1[SIZE];
int match2[SIZE];

int color[SIZE];

bool dfs(int N,int u){
	for(int i=0;i<N;i++)
		if(mat[u][i] && color[i]){
			color[i]=1;
			if(match2[i]==-1){
				match2[i]=u;
				match1[u]=i;
				return true;
			}
			else{
				bool flag = dfs(N,match2[i]);
				if(flag){
					match2[i]=u;
					match1[u]=i;
					return true;
				}
			}
		}
	
	return false;
}

int maxMatch(int N){
	memset(match1,-1,sizeof(match1));
	memset(match2,-1,sizeof(match2));
	for(int i=0;i<N;i++){
		memset(color,0,sizeof(color));
		dfs(N,i);
	}
	int ret = 0;
	for(int i=0;i<N;i++)
		if(match1[i]!=-1) ++ret;
	return ret;
}

int main()
{
}