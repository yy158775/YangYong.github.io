	#include <bits/stdc++.h>
	#define ms(a,b) memset(a,b,sizeof(a))
	using namespace std;
	const int Maxn=105;
	const int Inf=1<<30;
	const double eps=1e-5;
	struct Edge{
		int to,next;
	}edge[Maxn<<1];
	
	double d[Maxn];
	int Nedge;
	int N,M,m;
	double cha[105],pol[105];
	int v[Maxn],c[Maxn],sz[Maxn],head[Maxn];
	
	 
//	inline int Min(int n,int m) {return n<m?n:m;}
//	inline int Max(int n,int m) {return n>m?n:m;}
	inline int read() 
	{
		int w=0,x=0;char ch=0;
		while (!isdigit(ch)) {w|=ch=='-';ch=getchar();}
		while (isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
		return w?-x:x;
	}
	
	inline void Add_Edge(int u,int v) {//�ڽӱ�ͼ
		edge[Nedge]=(Edge){v,head[u]};
		head[u]=Nedge++;
	}
	
	struct tree
	{
	double sum1,sum2;
	double rat;	
	}f[105][105];
	
	
	//m is  N-M;
	inline void dfs(int u,int fa) 
	{//������
		sz[u]=1;//����ǰ�ڵ�������ڵ�����Ϊ1
		f[u][0].sum1 = f[u][0].sum2 = f[u][0].rat = 0;
		f[u][1].sum1 = cha[u];
		f[u][1].sum2 = pol[u];
		f[u][1].rat = cha[u]/pol[u];
		//��ʼ��
		for (int i=head[u];i!=-1;i=edge[i].next) 
		{//ר��for
			int v=edge[i].to;
			if (v==fa) continue;//���v=fa��ô������
			dfs(v,u);//�ݹ�����
			sz[u]+=sz[v];//�������ĸ����ӵ��Լ�����
			for (int j=min(m,sz[u]);j>1;j--) //�Լ����м��� 
			for (int k=1;k<=min(j,sz[v]);k++) // k = j  f[u][0] ֮ǰ��Ϊ0  
					//f[u][j]=Max(f[u][j],f[u][j-k]+f[v][k]);//����
			{
			if(j == k) continue;//j >= k 
			//if((fabs(f[u][j-k].sum1 - 0) < eps) && ((j-k) > 1))   continue;   //��֤����Ϊ j  			
			if((fabs(f[u][j-k].sum1 - 0) < eps)) continue;
			if(f[u][j].rat < (f[u][j-k].sum1 + f[v][k].sum1) / (f[u][j-k].sum2 + f[v][k].sum2)) //��һҪ��f[u][j-k]Ϊ0�� 
				{
				f[u][j].rat =  (f[u][j-k].sum1 + f[v][k].sum1) / (f[u][j-k].sum2 + f[v][k].sum2);
				f[u][j].sum1 = f[u][j-k].sum1 + f[v][k].sum1;
				f[u][j].sum2 = f[u][j-k].sum2 + f[v][k].sum2;
				}
			
			}		
		}
		//for (int i=min(m,sz[u]);i>0;i--) f[u][i]=f[u][i-1]+d[u];
	} 
	
	int main()
	{
		//freopen("in.txt","r",stdin);
		ms(head,-1);
		cin>>N>>M;
		for(int i = 0;i <= N;i++)
			for(int j = 0;j <= M;j++)	
				f[i][j].sum1 = f[i][j].sum2 = f[i][j].rat =  0;
		for(int i = 1;i <= N;i++)
			cin>>cha[i];
		for(int i = 1;i <= N;i++)
			cin>>pol[i];
		m=N-M;
		
		for (int i=1;i < N;i++) 
		{
			int a=read(),b=read();
			Add_Edge(a,b);
			Add_Edge(b,a);
		}
		
		dfs(1,0);
		//cout<<"78\n";
		double maxv = 0;
		for(int i = 1;i <= N;i++)
			maxv = max(maxv,f[i][m].rat);
		//printf("%.1f",maxv);
		printf("%.1lf\n",maxv);
	}
