#[Link Partly Reverse](http://www.careercup.com/question?id=15138683)#

Reverse Linked list in parts iteratively.

ex 1->2->3->4->5->6->7->8 and if 'parts' is 3.

o/p = 3->2->1->6->5->4->8->7.


#[Vending Machine Problem](http://www.careercup.com/question?id=15139685)#

一开始认为是一个完全背包问题，但受到评论里面的提示知道，vending machine里面的每种硬币的数量是有限的，那么这道题又变成了
多重背包了

其实背包问题求最小值最大值都是可以的

#[最大团问题](http://www.careercup.com/question?id=15148712)#

>Given N sets of integers, remove some sets so that the remaining all sets are disjoint with one another. Find the optimal solution so that the number of sets remaining at the end is maximum.
please explain your algorithm properly rather than pasting code .

##分析##

题目构造数学模型很简单，每一个集合看成一个点，如果两个集合中有相同的数字，则这两个集合对应的点相连接。最后会构成一个无向图，我们就是要求这个图的最大独立集。要求一个图的最大独立集就是求其补图的最大团。
##最大团##
这里介绍一下最大团
>给定一个无向图G=(V,E)，如果U属于E，且任意(u,v)属于U，且同时又属于E，则称U是G的完全子图



