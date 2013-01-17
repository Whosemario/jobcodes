#include<iostream>
#include<string.h>

using namespace std;

#define SIZE 100

int mat[SIZE][SIZE]; /*Õºæÿ’Û*/

int match1[SIZE];
int match2[SIZE];

int queue[SIZE];
int head,tail;

int pre[SIZE];

int maxMatch(int N){
	int ret = 0;
	memset(match1,-1,sizeof(match1));
	memset(match2,-1,sizeof(match2));

	for(int i=0;i<N;i++){
		memset(pre,-1,sizeof(pre));
		head = tail = 0;
		queue[tail++] = i;
		while(head < tail && match1[i]==-1){
			int u = queue[head++];
			for(int j =0;j<N&&match1[i]==-1;j++)
				if(mat[u][j] && pre[j]==-1){
					queue[tail++] = match2[j];
					pre[j]=u;
					if(queue[tail-1]<0){
						for(int t=j,k=0;t>=0;j=t){
							match2[j]=k=pre[j];
							t=match1[k];
							match1[k]=j;
						}
					}
				}
		}
	}
}

int main()
{
}