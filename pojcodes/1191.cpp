#include<iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;

#define area(a1,b1,a2,b2) (sum[a2][b2]-sum[a1-1][b2]-sum[a2][b1-1]+sum[a1-1][b1-1])
#define MAXN 1000000000

int mat[9][9];
int dp[9][9][9][9][15];
int sum[9][9];

int dfs(int x1,int y1,int x2,int y2,int num){
    if(dp[x1][y1][x2][y2][num]!=-1)
        return dp[x1][y1][x2][y2][num];
    if(num==1){
        return area(x1,y1,x2,y2)*area(x1,y1,x2,y2);
    }
    int res = MAXN;
    //horizontal
    for(int i=x1;i<x2;i++){
       int tmp = area(x1,y1,i,y2)*area(x1,y1,i,y2);
       tmp += dfs(i+1,y1,x2,y2,num-1);
       if(tmp < res) res = tmp;
       tmp = area(i+1,y1,x2,y2)*area(i+1,y1,x2,y2);
       tmp += dfs(x1,y1,i,y2,num-1);
       if(tmp < res) res = tmp;
    }
    //vertical
    for(int i=y1;i<y2;i++){
       int tmp = area(x1,y1,x2,i)*area(x1,y1,x2,i);
       tmp += dfs(x1,i+1,x2,y2,num-1);
       if(tmp < res) res = tmp;
       tmp = area(x1,i+1,x2,y2)*area(x1,i+1,x2,y2);
       tmp += dfs(x1,y1,x2,i,num-1);
       if(tmp < res) res = tmp;
    }
    
    dp[x1][y1][x2][y2][num]=res;
    return res;
}

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=8;i++)
      for(int j=1;j<=8;j++)
         scanf("%d",&mat[i][j]);
    
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=8;i++)
       for(int j=1;j<=8;j++){
           sum[i][j] = mat[i][j]+sum[i][j-1]+sum[i-1][j] - sum[i-1][j-1];
       }
    
    memset(dp,-1,sizeof(dp));
    
    int res = dfs(1,1,8,8,n);

    double avg = sum[8][8]*1.0/n;
    
    printf("%.3lf\n",sqrt((double)res/n-avg*avg));
    
    system("pause");
}
