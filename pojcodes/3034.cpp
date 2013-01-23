#include<iostream>
#include<string.h>
using namespace std;

#define ABS(x) ((x)>=0?(x):-(x))

int dp[1002][31][31];
int mat[1002][31][31];
int sumR[1002][31][31];
int sumC[1002][31][31];

int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}

int get(int k, int x1,int y1,int x2,int y2){
    int dx = x2-x1;
    int dy = y2-y1;
    int g = gcd(ABS(dx),ABS(dy));
    int ret = 0;
    if(mat[k][x1][y1]==k) ret++;
    if(mat[k][x2][y2]==k) ret++;
    if(g==1) return ret;
    else{
       dx/=g;dy/=g;
	   if(dx>0){
		   for(int x=x1+dx,y=y1+dy;x<x2;x+=dx,y+=dy)
			  if(mat[k][x][y]==k)
				 ret++;
	   }
	   else{
		   for(int x=x1+dx,y=y1+dy;x>x2;x+=dx,y+=dy)
			  if(mat[k][x][y]==k)
				 ret++;
	   }
       return ret;
    }
}

int main()
{
    int n,d,m;
    while(scanf("%d%d%d",&n,&d,&m)&&n){
       memset(mat,0,sizeof(mat));
       
       int maxCnt = 0;
       for(int i=0;i<m;i++){
		  int x,y,t;
          scanf("%d%d%d",&x,&y,&t);
          mat[t][x+6][y+6]=t;
          if(t>maxCnt) maxCnt = t;
       }
       n+=10;
       // Row
       for(int k=1;k<=maxCnt;k++)
          for(int i=1;i<=n;i++){
             sumR[k][i][0]=0;
             for(int j=1;j<=n;j++)
               if(mat[k][i][j]==k) sumR[k][i][j]=sumR[k][i][j-1]+1;
               else sumR[k][i][j]=sumR[k][i][j-1];
          }
       //Column
       for(int k=1;k<=maxCnt;k++)
          for(int j=1;j<=n;j++){
             sumC[k][0][j]=0;
             for(int i=1;i<=n;i++)
                if(mat[k][i][j]==k) sumC[k][i][j]=sumC[k][i-1][j]+1;
                else sumC[k][i][j] = sumC[k][i-1][j];
          } 
       memset(dp,0,sizeof(dp));
       for(int k=1;k<=maxCnt;k++)
          for(int i=1;i<=n;i++)
             for(int j=1;j<=n;j++){
                 if(mat[k][i][j]==k) dp[k][i][j] = dp[k-1][i][j]+1;
                 else dp[k][i][j] = dp[k-1][i][j];
                 for(int s=1;s<=d;s++){
                    // down
                    if(i+s<=n&&dp[k-1][i+s][j]+sumC[k][i+s][j]-sumC[k][i-1][j] > dp[k][i][j])
                        dp[k][i][j] = dp[k-1][i+s][j]+sumC[k][i+s][j]-sumC[k][i-1][j];
                    // up
                    if(i-s>0&&dp[k-1][i-s][j]+sumC[k][i][j]-sumC[k][i-s-1][j] > dp[k][i][j])
                        dp[k][i][j] = dp[k-1][i-s][j]+sumC[k][i][j]-sumC[k][i-s-1][j];
                    // left
                    if(j-s>0&&dp[k-1][i][j-s]+sumR[k][i][j]-sumR[k][i][j-s-1] > dp[k][i][j])
                        dp[k][i][j] = dp[k-1][i][j-s]+sumR[k][i][j]-sumR[k][i][j-s-1];
                    // right
                    if(j+s<=n && dp[k-1][i][j+s]+sumR[k][i][j+s]-sumR[k][i][j-1] > dp[k][i][j])
                        dp[k][i][j] = dp[k-1][i][j+s]+sumR[k][i][j+s]-sumR[k][i][j-1];
                 }
                 for(int x=1;x<=d;x++)
                   for(int y=1;y<=d;y++)
                      if(x*x+y*y<=d*d){
                          int tmp = 0;
                          // right-down
                          if(i+x<=n&&j+y<=n){
                             tmp = get(k,i,j,i+x,j+y);
                             if(dp[k-1][i+x][j+y]+tmp > dp[k][i][j])
                                dp[k][i][j] = dp[k-1][i+x][j+y]+tmp;
                          }
                          // right-up
                          if(i-x>0&&j+y<=n){
                              tmp = get(k,i,j,i-x,j+y);
                              if(dp[k-1][i-x][j+y]+tmp > dp[k][i][j])
                                 dp[k][i][j] = dp[k-1][i-x][j+y]+tmp;
                          }
                          // left-down
                          if(i+x<=n&&j-y>0){
                              tmp = get(k,i,j,i+x,j-y);
                              if(dp[k-1][i+x][j-y]+tmp > dp[k][i][j])
                                 dp[k][i][j] = dp[k-1][i+x][j-y]+tmp;
                          }
                          // left-up
                          if(i-x>0&&j-y>0){
                              tmp = get(k,i,j,i-x,j-y);
                              if(dp[k-1][i-x][j-y]+tmp > dp[k][i][j])
                                 dp[k][i][j] = dp[k-1][i-x][j-y]+tmp;
                          }
                      }
             }
             
        int res = 0;
        for(int i=1;i<=n;i++)
           for(int j=1;j<=n;j++)
             for(int k=1;k<=maxCnt;k++)
                if(dp[k][i][j] > res)
                    res=dp[k][i][j];
        
        printf("%d\n",res);
    }    
}
