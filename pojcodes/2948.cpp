#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 503

int matY[SIZE][SIZE];
int matB[SIZE][SIZE];
int sumY[SIZE][SIZE];
int sumB[SIZE][SIZE];
int dp[SIZE][SIZE];

int main()
{
    int N,M;
    while(scanf("%d%d",&N,&M)&&N&&M){
    
        for(int i=1;i<=N;i++)
           for(int j=1;j<=M;j++)
              scanf("%d",&matY[i][j]);
        for(int i=1;i<=N;i++)
           for(int j=1;j<=M;j++)
              scanf("%d",&matB[i][j]);
        
        // process Y
        for(int i=1;i<=N;i++){
           sumY[i][0]=0;
           for(int j=1;j<=M;j++)
              sumY[i][j]=sumY[i][j-1]+matY[i][j];
        }
        //process B
        for(int j=1;j<=M;j++){
           sumB[0][j]=0;
           for(int i=1;i<=N;i++)
              sumB[i][j] = sumB[i-1][j]+matB[i][j];
        }
        
        memset(dp,0,sizeof(dp));
        
        for(int i=1;i<=N;i++)
          for(int j=1;j<=M;j++){
              // goto Y
              dp[i][j]=dp[i-1][j]+sumY[i][j];
              // goto B
              int tmp = dp[i][j-1]+sumB[i][j];
              if(tmp>dp[i][j])
                 dp[i][j]=tmp;
          }
        printf("%d\n",dp[N][M]);
    }
}
