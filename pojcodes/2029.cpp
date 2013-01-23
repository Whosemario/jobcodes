#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 102

char mat[SIZE][SIZE];
int sumW[SIZE];
int sumH[SIZE][SIZE];

int main()
{
    int N;
    int W,H;
    while(scanf("%d",&N) && N){
        scanf("%d%d",&W,&H);
        
        memset(mat,0,sizeof(mat));
        
        for(int i =0;i<N;i++){
            int x,y;
            scanf("%d%d",&y,&x);
            mat[x][y]=1;
        }
        
        memset(sumH,0,sizeof(sumH));
        for(int j=1;j<=W;j++){
            for(int i=1;i<=H;i++){
                if(mat[i][j]){
                   sumH[i][j] = sumH[i-1][j] + 1;
                }
                else{
                   sumH[i][j] = sumH[i-1][j];
                }
            }
        }
        
        int S,T;
        scanf("%d%d",&S,&T);
        
        int res = 0;
        for(int i=T;i<=H;i++){
            sumW[0]=0;
            for(int j=1;j<=W;j++)
               sumW[j] = sumW[j-1]+sumH[i][j]-sumH[i-T][j];
            for(int j=S;j<=W;j++)
              if(res < sumW[j]-sumW[j-S])
                 res = sumW[j]-sumW[j-S];
        }
        
        printf("%d\n",res);
    }
}
