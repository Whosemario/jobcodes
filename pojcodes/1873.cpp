#include<iostream>
#include<string.h>
using namespace std;

#define SIZE 7500

int dp[22][SIZE*2+10];
int Carr[22];
int Garr[22];

int main()
{
	int C,G;
	scanf("%d%d",&C,&G);
	for(int i=1;i<=C;i++)
		scanf("%d",&Carr[i]);
	for(int i=1;i<=G;i++)
		scanf("%d",&Garr[i]);

	memset(dp,0,sizeof(dp));

	int lim = SIZE*2;
	dp[0][SIZE]=1;
	for(int i=1;i<=G;i++)
		for(int j=0;j<=lim;j++)
			if(dp[i-1][j]!=0){
				for(int k=1;k<=C;k++)
					dp[i][j+Carr[k]*Garr[i]]+=dp[i-1][j];
			}

	printf("%d\n",dp[G][SIZE]);

	system("pause");
}