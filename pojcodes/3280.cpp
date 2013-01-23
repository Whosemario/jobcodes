#include<iostream>
#include<string.h>
using namespace std;

#define MAXN 2003

int dp[MAXN][MAXN];
int hash[30][2];

char id[MAXN];

int dfs(int left, int right){
    if(left==right)
      return 0;
    if(left-right==1 && id[left]==id[right])
      return 0;
    if(dp[left][right]!=-1)
      return dp[left][right];
    
    int ret = 1000000000;
    int tmp;
    if(id[left]==id[right]){
        tmp = dfs(left+1,right-1);
        if(tmp < ret)
          ret=tmp;
    }
    //delete left
    tmp = hash[id[left]-'a'][1]+dfs(left+1,right);
    if(tmp < ret) ret=tmp;
    //add left
    tmp = hash[id[right]-'a'][0]+dfs(left,right-1);
    if(tmp<ret) ret=tmp;
    //delete right
    tmp = hash[id[right]-'a'][1]+dfs(left,right-1);
    if(tmp<ret) ret=tmp;
    //add right
    tmp = hash[id[left]-'a'][0]+dfs(left+1,right);
    if(tmp<ret) ret=tmp;
    
    dp[left][right]=ret;
    
    return ret;
}

int main()
{
    int N,M;
    scanf("%d%d",&N,&M);
    scanf("%s",id);
    
    //puts(id);
    
    memset(hash,-1,sizeof(hash));
    
    char cc;
    cc=getchar();
    for(int i=0;i<N;i++){
        char c;
        int x,y;
        scanf("%c %d %d",&c,&x,&y);
        hash[c-'a'][0]=x;
        hash[c-'a'][1]=y;
        cc=getchar();
    }
    
    memset(dp,-1,sizeof(dp));
    
    int res = dfs(0,M-1);
    
    printf("%d\n",res);
    
    system("pause");
}
