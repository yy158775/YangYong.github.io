#include<bits/stdc++.h>
using namespace std;
int N,M,m;
vector<int>tu[105];
double chan[105],pol[105];
double dp[105][105];
double res[105]; 
int size[105]; 
const double inf = 0x3fffffff;

void dfs(int u,int v)
{
	dp[u][0] = 0;
	dp[u][1] = res[u];
	cout<<res[1]<<endl;
	cout<<dp[u][1]<<" 15 "<<dp[u][0]<<endl<<">\n";
	size[u] = 1;
	for(int i = 0;i < tu[u].size();i++)
	{
		if(tu[u][i] == v) continue;
		dfs(tu[u][i],u);
		size[u]+=size[tu[u][i]];
		for(int j = min(m,size[u]);j > 1;j--)
			for(int k = 1;k <= min(j,size[tu[u][i]]);k++)
			{
				if(k == j) continue;
				//if(fabs(dp[u][j-k]-0) < 1e-4) continue;  //防止凑不够M个但其实不太可能因为 
				if(dp[u][j] < dp[u][j-k] + dp[tu[u][i]][k])
					dp[u][j] = dp[u][j-k] + dp[tu[u][i]][k];
			
			}
			
	}
}


bool judge(double x)
{

for(int i = 1;i <= N;i++)
	{
	res[i] = chan[i] - x*pol[i];
	cout<<"res[1] is "<<res[i]<<endl;	
	}
for(int i = 1;i <= 105;i++)	
	for(int j = 1;j <= 105;j++)
		dp[i][j] = -inf;
dfs(1,0);

double maxv = 0;

for(int i = 1;i <= N;i++)
 	maxv = max(maxv,dp[i][m]);
cout<<maxv<<endl;
if(maxv > x) return true;
else return false;
} 


int main()
{
	freopen("in.txt","r",stdin);
	int a,b;
	cin>>N>>M;
	m = N-M;
	for(int i = 1;i <= N;i++) cin>>chan[i];
	for(int i = 1;i <= N;i++) cin>>pol[i];
	for(int i = 1;i < N;i++)
	{
		cin>>a>>b;
		tu[a].push_back(b);
		tu[b].push_back(a);
	}
double r = 10000,l = 0;
double mid;

while(r-l > 1e-4)
{
mid = (r + l)/2.0;
if(judge(mid))
	l = mid;
else r = mid;	
}	

double ans = (r + l)/2;
printf("%.1f\n",ans);	
cout<<mid<<" "<<l<<" "<<r;
}



