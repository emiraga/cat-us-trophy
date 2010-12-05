#include<cstdio>
#include<algorithm>
#include<iostream>
#define Renew(x,c) x=max(x,c)
using namespace std;
const int inf=~0U>>3;
class splay
{
	int*A;int n;
	struct Tinfo 
	{
		int size,maxm,maxl,maxr,sum,value;
		Tinfo(int x=0):maxm(x),maxl(x),maxr(x),sum(x),value(x),size(1){}
		void Merge(const Tinfo&l,const Tinfo&r)
		{
			size=l.size+r.size+1;
			sum=l.sum+r.sum+value;
			maxl=max(l.maxl,l.sum+value+max(r.maxl,0));
			maxr=max(r.maxr,r.sum+value+max(l.maxr,0));
			maxm=max(l.maxm,r.maxm);
			Renew( maxm,value+max(l.maxr+r.maxl,0) );
			Renew( maxm,value+max(l.maxr,r.maxl) );
		}
	};
	struct node
	{
		Tinfo info;
		bool d;
		node*c[2],*p;
		void sc(node*_c,bool d)
		{c[d]=_c;_c->p=this;_c->d=d;}
		int& s()
		{return info.size;}
	}*root,*Null,*Now,Data[300000];
	typedef node* Node;
	Node new_node(int k)
	{
	     Now->info=Tinfo(k);
	     Now->c[0]=Now->c[1]=Null;
	     return Now++;	     
	}
	void upd(Node t)
	{
		t->info.Merge(t->c[0]->info,t->c[1]->info);
	}
	void rot(Node t)
	{
		node*p=t->p;bool d=t->d;
		p->sc(t->c[!d],d);
		p->p->sc(t,p->d);
		t->sc(p,!d);	
		upd(p);
		if(p==root) root=t;
	}
	void spl(Node x,Node f)
	{
		while(x->p!=f)
		{
			if(x->p->p==f) rot(x);
			else x->d==x->p->d?( rot(x->p),rot(x) ):( rot(x),rot(x) );
		}
		upd(x);
	}	
	Node select(int k)
	{
		int r;
		for(Node t=root;;)
		{		
			r=t->c[0]->s();
			if(r==k) return t;
			t=t->c[k>r];
			if(k>r) k-=r+1;
		}
	}
	Node get(int l,int r)
	{
		Node x=select(l);
		spl(x,Null);
		Node y=select(r);
		spl(y,x);
		return y->c[0];
	}
public:
	splay(int*A,int n):A(A),n(n)
	{		
		Now=Data;
		Null=new_node(0);Null->s()=0;Null->info.maxm=-inf;
		root=new_node(-inf);root->p=Null;
		Node p,q=root;
		for(int i=0;i<n;i++)
		{
			p=new_node(A[i]);
			q->sc(p,1);
			q=p;
		}
		Node last=new_node(-inf);
		q->sc(last,1);
		spl(last,Null);
	}
	int Max(int l,int r)
	{
		return get(l-1,r+1)->info.maxm;
	}
	void ins(int p,int x)
	{
		get(p-1,p);
		Node q=new_node(x);
		root->c[1]->sc(q,0);
		spl(q,Null);
	}
	void del(int p)
	{
		Node x;
		for(x=select(p);x->c[0]!=Null;rot(x->c[0]));
		if(x->c[1]==Null)
		{
			x->p->c[x->d]=Null;
			x->p->s()--;
			spl(x->p,Null);

			return;
		}
		x->p->sc(x->c[1],x->d);
		spl(x->c[1],Null);
		return;
	}
	void rep(int p,int x)
	{
		Node q=get(p-1,p+1);
		q->info=Tinfo(x);
		spl(q,Null);
	}
}*sp;
const int maxn=100000;
int A[maxn];
int main()
{
	int n,m;scanf("%d\n",&n);
	for(int i=0;i<n;i++)
		scanf("%d",A+i);
	sp=new splay(A,n);
	char c;int x,p;
	scanf("%d\n",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%c",&c);
		switch(c)
		{
			case 'I':scanf("%d %d",&p,&x),sp->ins(p,x);break;
			case 'D':scanf("%d",&p),sp->del(p);break;
			case 'R':scanf("%d %d",&p,&x),sp->rep(p,x);break;
			case 'Q':scanf("%d %d",&x,&p),printf("%d\n",sp->Max(x,p));break;
		}
		scanf("\n");
	}
}
