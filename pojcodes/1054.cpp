
#include<iostream>
#include<algorithm>
using namespace std;

#define MAXN 5003

struct Point{
    short x,y;
};
short hash[MAXN][MAXN];
Point rices[MAXN];
short dp[MAXN][MAXN];

bool cmp(Point a,Point b){
     if(a.x == b.x)
        return a.y < b.y;
     return a.x<b.x;
}

int C,R;

bool isOut(int x,int y){
     return x<=0 || x>R || y<=0 || y>C;
}
    
int main()
{

    int N;
    scanf("%d%d",&R,&C);
    scanf("%d",&N);
    
    memset(hash,-1,sizeof(hash));
    
    for(int i=0;i<N;i++){
       scanf("%d%d",&rices[i].x,&rices[i].y);
      
    }
    sort(rices,rices+N,cmp);

    for(int i=0;i<N;i++)
        hash[rices[i].x][rices[i].y] = i;   
      
    memset(dp,-1,sizeof(dp));
    
    int res = 0;
    for(int i=0;i<N;i++)
       for(int j=0;j<i;j++){
          int xi = rices[i].x, yi = rices[i].y;
          int xj = rices[j].x, yj = rices[j].y;
          int tx = 2*xj-xi, ty = 2*yj-yi;
          if(isOut(tx,ty)){
             dp[j][i] = 2;
          }
          else if(hash[tx][ty]!=-1 && dp[hash[tx][ty]][j]!=-1){
             dp[j][i] = dp[hash[tx][ty]][j] + 1;
             tx = 2*xi-xj;ty=2*yi-yj;
             if(isOut(tx,ty) && dp[j][i] > res && dp[j][i] > 2){
                 res = dp[j][i];
             }
          }
       }
    
    printf("%d\n",res);
    
    system("pause");
}
