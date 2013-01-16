#[Link Partly Reverse](http://www.careercup.com/question?id=15138683)#

Reverse Linked list in parts iteratively.

ex 1->2->3->4->5->6->7->8 and if 'parts' is 3.

o/p = 3->2->1->6->5->4->8->7.


#[Vending Machine Problem](http://www.careercup.com/question?id=15139685)#

一开始认为是一个完全背包问题，但受到评论里面的提示知道，vending machine里面的每种硬币的数量是有限的，那么这道题又变成了
多重背包了

其实背包问题求最小值最大值都是可以的

#[最大独立集问题](http://www.careercup.com/question?id=15148712)#

>Given N sets of integers, remove some sets so that the remaining all sets are disjoint with one another. Find the optimal solution so that the number of sets remaining at the end is maximum.
please explain your algorithm properly rather than pasting code .   

##分析##

题目构造数学模型很简单，每一个集合看成一个点，如果两个集合中有相同的数字，则这两个集合对应的点相连接。最后会构成一个无向图，我们就是要求这个图的最大独立集。要求一个图的最大独立集就是求其补图的最大团。
##最大团##
这里介绍一下最大团
>给定一个无向图G=(V,E)，如果U属于E，且任意(u,v)属于U，且同时又属于E，则称U是G的完全子图。
>G的完全子图U是G的最大团当且仅当U不包含在G的更大的完全子图中，即U就是最大的完全子图。

如下图：

![](.\pictures\graph.jpg)

此图的最大团有：

![](.\pictures\maxclique1.jpg) ![](.\pictures\maxclique2.jpg) ![](.\pictures\maxclique3.jpg)

那怎样求一个图的呢？朴素的搜索将会是n*2^n的时间复杂度，所以需要进行剪枝，并记录一些状态，即DP+DFS的思想。先把代码写出来。

	#define SIZE 102
	int mat[SIZE][SIZE];  /*图矩阵*/
	int dp[SIZE];
	int mx;
	int stack[SIZE][SIZE];
	void dfs(int N,int num,int step){
	
		if(num==0){
			if(step > mx){
				mx=step;
			}
			return ;
		}
	
		for(int i=0;i<num;i++){
			int k = stack[step][i];
			if(step+N-k<=mx) return ;
			if(step+dp[k]<=mx) return ;
			int cnt = 0;
			for(int j=i+1;j<num;j++)
				if(mat[k][stack[step][j]]){
				     stack[step+1][cnt++]=stack[step][j];
				}
			dfs(N,cnt,step+1);
		}
	}
	
	void run(int N){
	
		mx =0;
		for(int i=N-1;i>=0;i--){
			int sz =0;
			for(int j=i+1;j<N;j++)
				if(mat[i][j]) stack[1][sz++]=j;
			dfs(N,sz,1);
			dp[i]=mx;
		}
	}
	
下面简单地说一下思路（节点下标是从0开始的）：  
dp[i]表示从i到n-1中的最大团的节点数。   
枚举每一个节点，看这个节点与哪些编号大于它的节点相连，记录这些节点，然后递归地处理这些节点。。。    
怎样去做剪枝那？    
假如已经到x个节点在“团”里的状态，处理到了第k个节点，判断   
	x+n-k <= mx   
和   
	x+dp[k] <= mx     
两个条件。只要有一个成立，则没有必要继续下去了。    
##最大独立集##
**最大独立集就是其补图的最大团**      
###二分图的最大独立集###
如果一个图是二分图，那么它的最大独立集就是多项式时间可以解决的问题了 |最大独立集| = |V|-|最大匹配数|    
**证明：**   
设最大独立集数为U