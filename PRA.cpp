#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<time.h>
using namespace std;
int type;
int s;
int *A;
int f;
int range;
void input()
{
	cout<<"Enter Size of data:";
	cin>> s;
	A=new int [s];
	if(type==1)
	{
		cout<<"Enter maximum range of reference string:";
		cin>> range;
		srand(time(0));
		cout<<"Reference String:";
		for(int i=0;i<s;i++)
		{
			A[i]=rand()%(range+1);
			cout<<A[i]<<" ";
		}
		cout<<endl;
	}
	else if(type==2)
	{
		cout<<"Enter Data:";
		for(int i=0;i<s;i++)
		{
			cin>>A[i];
		}
	}
	cout<<"Enter Frame size:";
	cin>>f;
	cout<<"Algorithm\t"<<setw(10)<<"PageFaults\t"<<setw(10)<<"HitCount\t"<<setw(10)<<"Page Fault Ratio\t"<<setw(10)<<" Hit Ratio"<<endl;
}
class bitarray{
	public:
	int data;
	bool bit;
	bitarray(int d=-1,bool b=false)
	{
		data=d;
		bit=b;
	}
};
class node{
	public:
		int data;
		node* next;
		node(int d=-1,node* n=NULL)
		{
			data=d;
			next=n;
		}
};
class Queue{
	node* head;
	node* tail;
	public:
		Queue()
		{
			head=NULL;
			tail=head;
		}
		void enqueue(int d)
		{
			if(head==NULL)
			{
				head=new node(d);
				tail=head;
			}
			else{
				node*temp=new node(d,tail->next);
				tail->next=temp;
				tail=temp;
			}
		}
		void dequeue()
		{
			if(isEmpty())
			{
				cout<<"Queue is Empty!"<<endl;
			}
			else{
				node*temp=head;
				head=head->next;
				delete temp;
			}
		}
		void remove(int d)
		{
			if(head->data==d)
			{
				node*temp=head;
				head=head->next;
				delete temp;
			}
			else
			{
				node* temp = head;
				node* temp1 = temp->next;
				while(temp1->data!=d)
				{
					temp1=temp1->next;
					temp=temp->next;
				}
				temp->next=temp1->next;
				delete temp1;
			}
		}
		bool check(int d)
		{
			node* temp=head;
			while(temp!=NULL)
			{
				if(temp->data==d)
				{
					return true;
				}
				temp=temp->next;
			}
			return false;
		}
		void print()
		{
			node* temp=head;
			while(temp!=NULL)
			{
				cout<<temp->data<<"\t";
				temp=temp->next;
			}
		}
		bool isEmpty()
		{
			if(head==NULL)
			{
				return true;
			}
			return false;
		}
		int size()
		{
			node* temp=head;
			int count=0;
			while(temp!=NULL)
			{
				temp=temp->next;
				count++;
			}
			return count;
		}
		~Queue()
		{		while(head!=NULL)
				{
				node*temp=head;
				head=head->next;
				delete temp;
				}
		}
};
class cstack{
	bitarray *d;
	int top;
	public:
		cstack()
		{
			 d=new bitarray[f];
			top=0;
		}
	bool check(int n)
	{
		for(int i=0;i<f;i++)
		{
			if( n == d[i].data )
			{
				return true;
			}
		}
		return false;
	}
	void inc_top()
	{
		top++;
		}	
	void reset_top()
	{
		top=0;
		}	
	void push(int n)
	{
			d[top%f].data=n;
			top++;
	}
	int pop()
	{
		int t=d[top].data;
		d[top].data=-1;
		top--;
		return t;
	}
	void set_bit(int n)
	{
		int i;
		for(i=0;i<f;i++)
		{
			if(n==d[i].data)
			{
				d[i].bit=true;
				break;
			}
		}
	}
	void reset_bit()
	{
		d[top%f].bit=false;
	}
	bool get_bit()
	{
		return d[top%f].bit;
	}
	void print()
	{
		for(int i=0;i<f;i++)
		{
			cout<<d[i].data<<"- "<<d[i].bit<<"\t";
		}
	}
	~cstack()
	{
		delete[] d;
	}
};
class FIFO{
	int page_fault;
	int hit_count;
	cstack d;
	public:
		FIFO()
		{
			page_fault=0;
			hit_count=0;
		}
		void algo()
		{
			for(int i=0;i<s;i++)
			{
				if(!d.check(A[i]))
				{
					d.push(A[i]);
					page_fault++;
				}
			}
			hit_count=s-page_fault;
			cout<<"FIFO\t"<<setw(9)<<"\t"<<page_fault<<setw(10)<<"\t"<<hit_count<<setw(10)<<"\t"<<((float(page_fault)/(page_fault+hit_count))*100)<<"%"<<setw(10)<<"\t"<<((float(hit_count)/(page_fault+hit_count))*100)<<"%"<<endl;
		}
		void reset()
		{
			d.reset_top();
			for(int i=0;i<f;i++)
			{
				d.push(-1);
			}
			d.reset_top();
			page_fault=0;
		}
};
class LRU{
	int page_fault;
	int hit_count;
	Queue q;
	public:
		LRU()
		{
			page_fault=0;
			hit_count=0;
		}
		void algo()
		{
			for(int i=0;i<s;i++)
			{
				if(q.size()!=f && !q.check(A[i]))
				{
					q.enqueue(A[i]);
					page_fault++;
				}
				else if(q.size()==f && !q.check(A[i]))
				{
					q.dequeue();
					q.enqueue(A[i]);
					page_fault++;
				}
				else if(q.check(A[i]))
				{
					q.remove(A[i]);
					q.enqueue(A[i]);
				}
			}
			hit_count=s-page_fault;
			cout<<"LRU\t"<<setw(10)<<"\t"<<page_fault<<setw(10)<<"\t"<<hit_count<<setw(10)<<"\t"<<((float(page_fault)/(page_fault+hit_count))*100)<<"%"<<setw(10)<<"\t"<<((float(hit_count)/(page_fault+hit_count))*100)<<"%"<<endl;
		}
		void reset()
		{
			while(!q.isEmpty())
			{
				q.dequeue();
			}
			page_fault=0;
		}
};
class SCA{
	cstack d;
	int page_fault;
	int hit_count;
	public:
		SCA()
		{
			page_fault=0;
			hit_count=0;
		}
		void algo()
		{
			for(int i=0;i<s;i++)
			{
				if(!d.check(A[i]) && !d.get_bit())
				{
					d.push(A[i]);
					page_fault++;
				}
				else if(d.get_bit())
				{
			
					d.reset_bit();
					d.inc_top();
					i--;
				}
				else if(d.check(A[i]))
				{
					d.set_bit(A[i]);
				}
			}
			hit_count=s-page_fault;
		cout<<"SCA\t"<<setw(10)<<"\t"<<page_fault<<setw(10)<<"\t"<<hit_count<<setw(10)<<"\t"<<((float(page_fault)/(page_fault+hit_count))*100)<<"%"<<setw(10)<<"\t"<<((float(hit_count)/(page_fault+hit_count))*100)<<"%"<<endl;
		}
		void reset()
		{
			d.reset_top();
			for(int i=0;i<f;i++)
			{
				d.push(-1);
				d.reset_bit();
			}
			d.reset_top();
		}
};
int main()
{
	type=0;
	do
	{
		cout<<"Press respective key to perform action..."<<endl;
		cout<<"1-Enter data automaticaly"<<endl;
		cout<<"2-Enter data manualy"<<endl;
		cout<<"0-Exit"<<endl;
		cin>>type;
		if(type==1 || type==2)
		{
			input();
			FIFO o;
			LRU o1;
			SCA o2;
			o.algo();
			o1.algo();
			o2.algo();
			cout<<endl;
			o.reset();
			o1.reset();
			o2.reset();
		}
		
	}
	while(type!=0);
	delete[] A;
}
