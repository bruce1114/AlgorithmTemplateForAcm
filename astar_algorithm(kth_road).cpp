//ACM-ICPC 2018 ������������Ԥ�� D. Made In Heaven ��k��· A_star*�㷨 ����ʽ����
//���յ㿪ʼ�������ҳ����е㵽�յ����̾��룬�Դ���Ϊ����������
//Ȼ�����㿪ʼ��spfa�Ҳ����ɳڵ������������ҳ�����·�����������˵㵽���ľ���ʹ˵㵽�յ����̾���
//�ĺͼ�����У���������̵�·��һ����ǰ�棨������� 
//����������������������ζ̵�·���ڶ��У�����̵�·�����ڶ��У������ѣ����� 

//�����ҳ���k��·�ĳ��ȣ������ܴ�ӡ������·�� 
#include<iostream>
#include<cstdio>
#include<memory.h>
#include<vector>
#include<queue>

using namespace std;
const int MAX=1e3+5;//������ 
const int INF=1e8;//�����ܵ���Ĵ�ֵ 

int num_point,num_edge,start,end,k_th;//��������������㣬�յ㣬k 
long long t;
bool flag[MAX];//���ڵϽ�˹�����б�����ҵ���̾���ĵ� 
int cnt;//��¼�յ���ѵĴ��� 
long long dis_dij[MAX];//����Ͻ�˹�����õ��Ľ�� 

struct pair_edge{//��ߵĽṹ 
	int to;//Ŀ�ĵ�ı�� 
	long long len;//��Ŀ�ĵľ��룻 
	pair_edge(int t=0,long long l=0):to(t),len(l) {}
};

struct pair_dij{//������еĽṹ���˶������Ż��Ͻ�˹���� 
	int point_index;//��ǰ��ı�ţ�
	long long dis;//����ʼ��ľ��룻 
	pair_dij(int a=0,long long b=0):point_index(a),dis(b) {} 
	friend bool operator < (pair_dij a,pair_dij b)
	{
		return a.dis>b.dis;//�������С�������� 
	}
};

struct pair_astar{//Astar�㷨�Ķ���ʹ�õĽṹ 
	int point_index;
	long long dis;//����ʼ��ľ��� 
	pair_astar(int a=0,long long b=0):point_index(a),dis(b) {}
	friend bool operator < (pair_astar a,pair_astar b)
	{
		return (a.dis+dis_dij[a.point_index]>b.dis+dis_dij[b.point_index]);//������dis+���յ�����dis ��С���� 
	}
};

vector<pair_edge>edge[MAX];//Astar������ʹ�� 
vector<pair_edge>edge_opposite[MAX];//�Ͻ�˹������ʹ�ã�����������ı��෴�������յ㵽��� 

void dij()//���Ż��ĵϽ�˹�������ڽӱ� 
{
	fill(dis_dij+1,dis_dij+num_point+1,INF);
	memset(flag,false,sizeof(flag));
	priority_queue<pair_dij>que;
	 
	dis_dij[end]=0;//���յ㵽��� 
	que.push(pair_dij(end,0));
	pair_dij qtop;
	
	while(!que.empty())
	{
		qtop=que.top(),que.pop();
		int index=qtop.point_index;
		int dis=qtop.dis;
		
		if(flag[index]) continue;
		flag[index]=true;
		
		int l=edge_opposite[index].size();
		for(int i=0;i<l;++i)
		{
			pair_edge tempedge=edge_opposite[index][i];
			int to=tempedge.to;
			long long len=tempedge.len;
			
			if(flag[to]) continue;
			if(dis_dij[to]>dis_dij[index]+len)
			{
				dis_dij[to]=dis_dij[index]+len;
				que.push(pair_dij(to,dis_dij[to]));
			}
		}
	}
}

bool astar()//astar�㷨���� 
{
	cnt=0;
	priority_queue<pair_astar>que;
	que.push(pair_astar(start,0));
	pair_astar qtop;
	
	while(!que.empty())
	{
		qtop=que.top(),que.pop();
		int index=qtop.point_index;
		long long dis=qtop.dis;
		
		if(index==end) ++cnt; 
		if(cnt==k_th)//�յ��k�γ��ѣ�����k��· 
		{
			return true;
		}
		
		int l=edge[index].size();
		for(int i=0;i<l;++i)
		{
			que.push(pair_astar(edge[index][i].to,qtop.dis+edge[index][i].len));//ͳͳ��� 
		}
	}
	
	//�޵�k��· 
	return false; 
}

int main()
{
	while(~scanf("%d%d",&num_point,&num_edge))
	{
		//��ͼ
		
		dij();//���ŵϽ�˹���� 
		//dis_dij[start]==INF,������յ��Ƿ���·���� 
		astar();
	}
	return 0;
}
