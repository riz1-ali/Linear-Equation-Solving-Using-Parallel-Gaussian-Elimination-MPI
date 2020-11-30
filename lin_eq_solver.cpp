#include "bits/stdc++.h"
#include <mpi.h>
using namespace std;
#define mp make_pair
#define f first
#define s second
int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	int tot_proc,proc_id,n;
	double A[102][102],B[102],trans[100010];
	MPI_Comm_size(MPI_COMM_WORLD,&tot_proc);
	MPI_Comm_rank(MPI_COMM_WORLD,&proc_id);
	MPI_Barrier(MPI_COMM_WORLD);
	if(!proc_id)
	{
		cin>>n;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin>>A[i][j];
		for(int i=0;i<n;i++)cin>>B[i];
		set<pair<int,int>> heaps;
		int nz[n];
		for(int i=0;i<n;i++)
		{
			int c=0;
			for(int j=0;j<n;j++)c+=A[j][i]!=0;
			heaps.insert(mp(c,i));
			nz[i]=c;
		}
		while(!heaps.empty())
		{
			pair<int,int> cur=*heaps.begin();
			heaps.erase(heaps.begin());
			int i=cur.s;
			double maxi=-1e5;
			int row=-1;
			for(int j=0;j<n;j++)
			{
				if(nz[j]<=0)continue;
				if(A[j][i]>maxi)
				{
					maxi=A[j][i];
					row=j;
				}
			}
			for(int j=0;j<n;j++)nz[j]-=A[row][j]!=0;
			nz[i]=0;
			heaps.clear();
			for(int i=0;i<n;i++)if(nz[i]>0)heaps.insert(mp(nz[i],i));
			if(row==i)continue;
			for(int j=0;j<n;j++)swap(A[i][j],A[row][j]);
			swap(B[i],B[row]);
		}
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)trans[i*n+j]=A[i][j];
	}
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(trans,n*n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(B,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
	for(int i=0;i<n*n;i++)A[i/n][i%n]=trans[i];
	for(int i=0;i<n;i++)
	{
		MPI_Bcast(&A[i][i],n-i,MPI_DOUBLE,i%tot_proc,MPI_COMM_WORLD);
		MPI_Bcast(&B[i],1,MPI_DOUBLE,i%tot_proc,MPI_COMM_WORLD);
		for(int j=proc_id;j<n;j+=tot_proc)
		{
			if(j<=i)continue;
			double r=0;
			if(A[i][i])r=A[j][i]/A[i][i];
			for(int k=0;k<n;k++)A[j][k]-=r*A[i][k];
			B[j]-=r*B[i];
		}
	}
	if(!proc_id)
	{
		for(int i=n-1;i>=0;i--)
		{
			for(int j=i+1;j<n;j++)B[i]-=A[i][j]*B[j];
			B[i]/=A[i][i];
		}
		cout<<fixed<<setprecision(2);
		for(int i=0;i<n;i++)cout<<B[i]<<" ";
		cout<<"\n";
	}
	MPI_Finalize();
	return 0;
}