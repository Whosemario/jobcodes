#include<iostream>
#include<string.h>

using namespace std;

#define SIZE 1050

#define getNext(x) (x&(-x))

int mat[SIZE][SIZE];
int c[SIZE][SIZE];

int S;

void update(int x,int y,int val){
	if(val+mat[x][y]<0){
		val = -mat[x][y];
	}

	mat[x][y]+=val;

	for(int i=x;i<=S;i+=getNext(i))
		for(int j=y;j<=S;j+=getNext(j))
			c[i][j] += val;
}

int query(int x,int y){
	if(x<=0 || y<=0) return 0;
	int ret = 0;
	for(int i=x;i>0;i-=getNext(i))
		for(int j=y;j>0;j-=getNext(j))
			ret+=c[i][j];
	return ret;
}

int main()
{
	int cmd;
	scanf("%d%d",&cmd,&S);
	while(scanf("%d",&cmd)&&cmd!=3){
		if(cmd == 1){
			int x,y,val;
			scanf("%d%d%d",&x,&y,&val);
			update(++x,++y,val);
		}
		else if(cmd == 2){
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			++x1;++y1;++x2;++y2;
			int res = query(x2,y2);
			res -= query(x1-1,y2);
			res -= query(x2,y1-1);
			res += query(x1-1,y1-1);
			printf("%d\n",res);
		}
	}
}