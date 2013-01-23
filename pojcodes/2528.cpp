#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

/* Segment Tree */
#define SIZE 80000
int TreeLeft[SIZE];
int TreeRight[SIZE];
int TreeCol[SIZE];
int colors[10004];

void buildTree(int k,int left,int right){
	if(left == right){
		TreeLeft[k]=left;
		TreeRight[k]=right;
	}
	else{
		TreeLeft[k]=left;
		TreeRight[k]=right;
		buildTree(k*2,left,(left+right)/2);
		buildTree(k*2+1,(left+right)/2+1,right);
	}
}

void insertSegment(int k,int left,int right,int col){
	if(left<=TreeLeft[k]&&right>=TreeRight[k]){
		TreeCol[k]=col;
	}
	else{
		//push children
		if(TreeCol[k]>0){
			TreeCol[k*2]=TreeCol[k*2+1]=TreeCol[k];
		}
		int mid = (TreeLeft[k]+TreeRight[k])/2;
		if(left<=mid)
			insertSegment(k*2,left,right,col);
		if(right>mid)
			insertSegment(k*2+1,left,right,col);
		int a = TreeCol[k*2];
		int b = TreeCol[k*2+1];
		if(a!=b)
			TreeCol[k]=0;
		else
			TreeCol[k]=a;
		
	}
}

void clearTree(){
	memset(TreeCol,0,sizeof(TreeCol));
}

void search(int k){
	if(TreeLeft[k]==TreeRight[k]){
		if(TreeCol[k]) colors[TreeCol[k]]=1;
	}
	else{
		if(TreeCol[k]){
			colors[TreeCol[k]]=1;
		}
		else{
			search(k*2);
			search(k*2+1);
		}
	}
}

/****************/
int arr[20005];
int M;
int posts[10005][2];

int find(int target){
	int low=0;
	int high = M-1;
	while(low<=high){
		int mid = (low+high)/2;
		if(arr[mid]==target)
			return mid+1;
		else if(target<arr[mid])
			high = mid-1;
		else 
			low = mid+1;
	}
	return -1;
}

int main()
{
	int ca;
	scanf("%d",&ca);
	buildTree(1,1,20010);
	while(ca--){
		int N;
		scanf("%d",&N);
		clearTree();
		M = 0;
		for(int i=0;i<N;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			arr[M++]=l;
			arr[M++]=r;
			posts[i][0]=l;
			posts[i][1]=r;
		}
		sort(arr,arr+M);
		int j=1;
		for(int i=1;i<M;i++)
			if(arr[i]!=arr[j-1])
				arr[j++]=arr[i];
		M=j;

		for(int i=0;i<N;i++){
			int l = find(posts[i][0]);
			int r = find(posts[i][1]);
			insertSegment(1,l,r,i+1);
		}

		memset(colors,0,sizeof(colors));
		search(1);

		int res = 0;
		for(int i=1;i<=N;i++)
			if(colors[i]) res++;

		printf("%d\n",res);
	}
}