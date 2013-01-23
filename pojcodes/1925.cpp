#include<iostream>
#include<string.h>
using namespace std;

int dp[1000005];
int points[5002][2];

int main()
{
    int test;
    scanf("%d",&test);
    while(test--){
       int N;
       scanf("%d",&N);
       for(int i=0;i<N;i++)
          scanf("%d%d",&points[i][0],&points[i][1]);
       memset(dp,-1,sizeof(dp));
       dp[points[0][0]] = 0;
       int res = -1;
       int a = points[0][1];
       for(int i=1;i<N;i++){
          int h = points[i][1];
          int x = points[i][0];
          for(int j=0;(long long)j*j<=(long long)a*h*2-(long long)a*a;j++)  /* trick 2*/
             if(x-j>=points[0][0]){
                 if(dp[x-j]!=-1){
                    if(i==N-1){
                       if(j==0 && (res==-1 || dp[x]<res))  /* trick 3 */
                          res = dp[x];
                       if(res==-1||dp[x-j]+1<res)
                          res = dp[x-j]+1;
                    }
                    else{
                       if(x+j>=points[N-1][0] && (res == -1 || dp[x-j]+1<res)) /* trick 1*/
                          res = dp[x-j]+1;
                       else if(x+j<points[N-1][0] && (dp[x+j]==-1 || dp[x-j]+1<dp[x+j]))
                          dp[x+j]=dp[x-j]+1;
                    }
                 }
             }
       }
       printf("%d\n",res);
    }
    system("pause");
}
