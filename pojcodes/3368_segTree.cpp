#include<iostream>
#include<string.h>
using namespace std;

int val[100003];
#define Max(x,y) ((x)>(y)?(x):(y))
#define Min(x,y) ((x)<(y)?(x):(y))
// segment tree
#define SIZE 400005
int TreeLeft[SIZE];
int TreeRight[SIZE];
int TreeFrq[SIZE];
int TreeLeftFrq[SIZE];
int TreeRightFrq[SIZE];


void buildTree(int k,int left,int right){
	if(left == right){
		TreeLeft[k] = TreeRight[k] = left;
		TreeFrq[k]=TreeLeftFrq[k]=TreeRightFrq[k]=1;
	}
	else{
		TreeRight[k]=right;
		TreeLeft[k]=left;
		int mid = (left+right)/2;
		buildTree(k*2,left,mid);
		buildTree(k*2+1,mid+1,right);
		// merge
		TreeFrq[k] = Max(TreeFrq[k*2],TreeFrq[k*2+1]);
		if(val[mid]==val[mid+1])
			TreeFrq[k] = Max(TreeFrq[k],TreeRightFrq[k*2]+TreeLeftFrq[k*2+1]);
		TreeLeftFrq[k] = TreeLeftFrq[k*2];
		if(val[mid]==val[mid+1] && val[mid]==val[left])
			TreeLeftFrq[k]+=TreeLeftFrq[k*2+1];
		TreeRightFrq[k] = TreeRightFrq[k*2+1];
		if(val[mid]==val[mid+1] && val[mid+1]==val[right])
			TreeRightFrq[k]+=TreeRightFrq[k*2];
	}
}

int query(int k,int left,int right){
	if(left<=TreeLeft[k] && right>=TreeRight[k]){
		return TreeFrq[k];
	}
	else{
		int mid = (TreeLeft[k]+TreeRight[k])/2;
		int ret = 0;
		if(right<=mid){
			return query(k*2,left,right);
		}
		else if(left>mid){
			return query(k*2+1,left,right);
		}
		else{
			int a = query(k*2,left,right);
			int b = query(k*2+1,left,right);
			ret = Max(a,b);
			if(val[mid]==val[mid+1]){
				a = Min(mid-left+1,TreeRightFrq[k*2]);
				b = Min(right-mid,TreeLeftFrq[k*2+1]);
				ret = Max(ret,a+b);
			}
			return ret;
		}
	}
}

int main()
{
	int n,q;
	while(scanf("%d",&n) && n){
		scanf("%d",&q);
		for(int i=1;i<=n;i++)
			scanf("%d",&val[i]);
		buildTree(1,1,n);
		for(int i=1;i<=q;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			if(l>r){
				int t = l;
				l = r;
				r = t;
			}
			printf("%d\n",query(1,l,r));
		}
	}
}