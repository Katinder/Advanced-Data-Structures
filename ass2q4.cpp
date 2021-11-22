#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct node
{
	int keys[4]; //array of keys 3 + extra
	bool leaf; //whether its a leaf node
	struct node *c1, *c2, *c3, *c4, *c5; //four child pointers
    struct node *parent;
	bool full; //flag for a full node
} ttfnode;

ttfnode* newnode(int key)
{
	ttfnode* nn=(ttfnode *)malloc(sizeof(ttfnode));
	nn->c1, nn->c2, nn->c3, nn->c4, nn->c5=NULL;
	nn->parent=NULL;
	nn->leaf=true;
	nn->full=false;
	nn->keys[0]=key;
	return nn;
}

ttfnode** treeroot;

ttfnode* searchkey(ttfnode* root,int key)
{
	//check in current node
	for(int i=0;i<3;i++)
	{
		if(root->keys[i]==key)
		{
			cout<<"Key already present"<<endl;
			return NULL;
		}
	}

	//move to child node
	if(key<root->keys[0])
	{	
		if(root->c1)
		return searchkey(root->c1, key);
		else
		{
			cout<<"Key not present\n";
			return root;
		}
	}
	
	else if(key<root->keys[1])
	{
		if(root->c2)
		return searchkey(root->c2, key);
		else
		{
			cout<<"Key not present\n";
			return root;
		}
	}
	else if(key<root->keys[2])
	{
		if(root->c3)
		return searchkey(root->c3, key);
		else
		{
			cout<<"Key not present\n";
			return root;
		}
	}
	else
	{
		if(root->c4)
		return searchkey(root->c4, key);
		else
		{
			cout<<"Key not present\n";
			return root;
		}
	}

}

void split(ttfnode *tosplit)
{
	if(tosplit->parent==NULL) //root node splitting
	{
		//create a new root node
		//copy the mid key
		ttfnode *newroot=newnode(tosplit->keys[2]);
		
		//create new sibling node
		ttfnode *newsib=newnode(tosplit->keys[3]);

		//delete curr node keys
		tosplit->keys[2]=0;
		tosplit->keys[3]=0;
		tosplit->full=false;
		newroot->leaf=false;

		//rearrange the children for all
		newroot->c1=tosplit;
		newroot->c2=newsib;
		newsib->c1=tosplit->c4;
		newsib->c2=tosplit->c5;
		tosplit->c4=NULL;
		tosplit->c5=NULL;

		//parent updations
		tosplit->parent=newroot;
		newsib->parent=newroot;


		//return new root as treeroot
		*treeroot=newroot;
	}

	else //leaf/internal node splitting
	{
		//create only 1 new node
		ttfnode *newsib=newnode(tosplit->keys[3]);

		//insert data to parent at the right place
			//if c(i) overflows
			//insertion at parent will be at i pos
		//check what child tosplit node is
		if(tosplit->parent->c1==tosplit) //need to split first child node
		{
			//insert at first pos of parent

			//shift all keys first
			for(int i=2;i>=0;i--)
			{
				tosplit->parent->keys[i+1]=tosplit->parent->keys[i];
			}

			tosplit->parent->keys[0]=tosplit->keys[2];
			//shift children till c2
			tosplit->parent->c5=tosplit->parent->c4;
			tosplit->parent->c4=tosplit->parent->c3;
			tosplit->parent->c3=tosplit->parent->c2;
			
			//normal tosplit node split
				//copy data to new sib node
			newsib->c1=tosplit->c4;
			newsib->c2=tosplit->c5;
			tosplit->c4=NULL;
			tosplit->c5=NULL;
			tosplit->keys[3]=0;
			tosplit->keys[2]=0;
			newsib->parent=tosplit->parent;

			//add the new c pointers to the parent
			tosplit->parent->c2=newsib;
			
		}

		else if(tosplit->parent->c2==tosplit) //2nd child overflow
		{
			//shift copy till i=1
			//shift copy pointers till c3
			for(int i=2;i>=1;i--)
			{
				tosplit->parent->keys[i+1]=tosplit->parent->keys[i];
			}

			tosplit->parent->keys[1]=tosplit->keys[2];
			//shift children till c2
			tosplit->parent->c5=tosplit->parent->c4;
			tosplit->parent->c4=tosplit->parent->c3;
			
			//normal tosplit node split
				//copy data to new sib node
			newsib->c1=tosplit->c4;
			newsib->c2=tosplit->c5;
			tosplit->c4=NULL;
			tosplit->c5=NULL;
			tosplit->keys[3]=0;
			tosplit->keys[2]=0;
			newsib->parent=tosplit->parent;

			//add the new c pointers to the parent
			tosplit->parent->c3=newsib;
		}

		else if(tosplit->parent->c3==tosplit)//3rd child overflow
		{
			//shift copy keys till i=2
			tosplit->parent->keys[3]=tosplit->parent->keys[2];

			tosplit->parent->keys[2]=tosplit->keys[2];
			//shift children till c4
			tosplit->parent->c5=tosplit->parent->c4;
			
			//normal tosplit node split
				//copy data to new sib node
			newsib->c1=tosplit->c4;
			newsib->c2=tosplit->c5;
			tosplit->c4=NULL;
			tosplit->c5=NULL;
			tosplit->keys[3]=0;
			tosplit->keys[2]=0;
			newsib->parent=tosplit->parent;

			//add the new c pointers to the parent
			tosplit->parent->c4=newsib;
		}

		else if(tosplit->parent->c4==tosplit)//last child overflow
		{
			//insert the overflow key at last
			tosplit->parent->keys[3]=tosplit->keys[2];
			//no pointer shift required

			//normal tosplit node split
				//copy data to new sib node
			newsib->c1=tosplit->c4;
			newsib->c2=tosplit->c5;
			tosplit->c4=NULL;
			tosplit->c5=NULL;
			tosplit->keys[3]=0;
			tosplit->keys[2]=0;
			newsib->parent=tosplit->parent;

			//add the new c pointers to the parent
			tosplit->parent->c5=newsib;
		}

		//call split on the parent if necessary
		if(tosplit->parent->keys[3] || tosplit->parent->full)
		{
			split(tosplit->parent);
		}
	}
}

//insert
//always happens on leaf nodes
void insert(ttfnode *root, int val)
{
	if(root==NULL)
	{
		return;
	}

	//node non-full
	if(!root->full)
	{
		int i=2;
		for(;i>=0;i--)
		{
			if(!root->keys[i])
			continue;

			else{

				if(val<root->keys[i])
				{
					//shift current key
					root->keys[i+1]=root->keys[i];
					//no need to shift children
					//bc insertion is at leaf always
		
				}

				else if(val>root->keys[i])//val > curr-key
				{
					i++; 
					break;
				}

			}
			
		}
		if(i<0) i=0;
		root->keys[i]=val;

		if(root->keys[3])
		root->full=true;

		if(root->full)
		{
			split(root);
			return;
		}

	}
}

//print tree
void ttfprint(ttfnode *root)
{
	if(root==NULL)
	{
		return;
	}

	for(int i=0;i<3;i++)
	{
		cout<<root->keys[i]<<" ";
	}
	cout<<endl;
	
	for(int i=0;i<3;i++)
	{
		if(i==0 && root->c1)
		{
			cout<<"c1 of "<<root->keys[0]<<" : ";
			ttfprint(root->c1);
		}
		
		
		else if(i==1 && root->c2)
		{	
			cout<<"c2 of "<<root->keys[0]<<" : ";
			ttfprint(root->c2);
		}

		else if(i==2 && root->c3)
		{
			cout<<"c3 of "<<root->keys[0]<<" : ";
			ttfprint(root->c3);}
	}
	
	if(root->c4)
	{
		cout<<"c4 of "<<root->keys[0]<<" : ";
		ttfprint(root->c4);}

}

int main()
{
	int val=4;

	cout<<val<<": ";
	ttfnode *root=newnode(val);
	treeroot=&root;

	cout<<"root: ";
	ttfprint(*treeroot);
	cout<<endl;

	cout<<"6: ";
	insert(searchkey(*treeroot,6),6);
	cout<<"root: ";
	ttfprint(*treeroot);
	cout<<endl;

	cout<<"12: ";
	insert(searchkey(*treeroot,12),12);
	cout<<"root: ";
	ttfprint(*treeroot);
	cout<<endl;

	cout<<"15: ";
	insert(searchkey(*treeroot,15),15);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"3: ";
	insert(searchkey(*treeroot,3),3);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"5: ";
	insert(searchkey(*treeroot,5),5);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"10: ";
	insert(searchkey(*treeroot,10),10);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"8: ";
	insert(searchkey(*treeroot,8),8);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"11: ";
	insert(searchkey(*treeroot,11),11);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"13: ";
	insert(searchkey(*treeroot,13),13);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"14: ";
	insert(searchkey(*treeroot,14),14);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"17: ";
	insert(searchkey(*treeroot,17),17);
	cout<<"root: ";
	ttfprint(*treeroot);

	cout<<endl<<"4: ";
	insert(searchkey(*treeroot,4),4);

	cout<<"\nFinal print: \nroot: ";
	ttfprint(*treeroot);

	return 0;
}
