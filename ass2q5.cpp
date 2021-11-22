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
void ttfdelete(ttfnode *root, int val);

ttfnode* searchkey(ttfnode* root,int key)
{
	//check in current node
	for(int i=0;i<3;i++)
	{
		if(root->keys[i]==key)
		{
			cout<<"Key present"<<endl;
			return root;
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
	
	else if(key<root->keys[1] || !root->keys[1])
	{
		if(root->c2)
		return searchkey(root->c2, key);
		else
		{
			cout<<"Key not present\n";
			return root;
		}
	}
	else if(key<root->keys[2] || !root->keys[2])
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

		if(tosplit->c1)
		{
			newsib->leaf=false;
		}

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
		if(tosplit->c1)
		{
			newsib->leaf=false;
		}

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
	cout<<" leaf: "<<root->leaf<<endl;
	
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


ttfnode * predecessor(ttfnode *root)
{
	//go to left child leaf

	if(!root->leaf) //go to the rightmost child of the rightmost child
	{	
		if(root->c4)
		return predecessor(root->c4);

		else if(root->c3)
		return predecessor(root->c3);

		else if(root->c2)
		return predecessor(root->c2);

		else if(root->c1)
		return predecessor(root->c1);
	}
	
	//if at leaf now
	return root;

}

ttfnode * successor(ttfnode *root)
{
	//go to right child leaf

	if(!root->leaf) //if at leaf now
	{	
		//else go to the leftmost child of the leftmost child
	
		if(root->c1) //first child always present
		return successor(root->c1);
	}
		return root;
	
}

void succreplace(ttfnode *root, int val)
{
	ttfnode *succ;

	//send next child for predecessor finding
	if(val==root->keys[0]) //always true for successor
	{
		succ=successor(root->c2);
	}

	//replace the original with this key
	root->keys[0]=succ->keys[0];

	//call delete on this successor key
	ttfdelete(succ, succ->keys[0]);
}

void predreplace(ttfnode *root, int val)
{
	ttfnode *pred;
	int pos=0;
	//send previous child for predecessor finding
	if(val==root->keys[0])
	{
		pos=0;
		pred=predecessor(root->c1);
	}
	

	else if(val==root->keys[1])
	{
		pos=1;
		pred=predecessor(root->c2);
	}

	else if(val==root->keys[2])
	{
		pos=2;
		pred=predecessor(root->c3);
	}

	else
	{
		//predecessor doesnt exist in leaf nodes
		//go for successsor
		succreplace(root, val);
	}

	//find the last key in this node
	int i=3; 
	for(;i>=0;i--)
	{
		if(pred->keys[i])
		{
			break;
		}
	}
	//replace the original with this key
	root->keys[pos]=pred->keys[i];

	//call delete on this predecessor key
	ttfdelete(pred, pred->keys[i]);
}


void ttfdelete(ttfnode *root, int val)
{
    //if leaf
        //check if 2/3 keys
            //direct delete
        //if 1 key only (underflow)
            //check if right-sibling has 2/3 keys
                ///borrow
                //involve parent key
            //else check if left-sibling has 2/3 keys
                ///borrow
                //involve parent key
            //else if both sibling has 1 key
                //merge with parent
                //ROOT UPDATION POSSIBLE HERE

    if(root->leaf)
    {
        if(root->keys[1]) //atleast 2 keys exist
        {
            //search position in node
            int i=0;
            for(i=0;i<3;i++)
            {
                if(val==root->keys[i])
                {
                    root->keys[i]=0;
                }

                else if(val<root->keys[i])
                {
                    root->keys[i-1]=root->keys[i];
                    if(root->keys[i+1]==0)
                    {
                        root->keys[i]=0;
                    }
                }
            }
        }

        else ///underflow
        {
            ttfnode *rightsib, *leftsib=NULL;
            int child=0;
            //find node position & sibs
            if(root->parent->c1==root)
            {
                child=0;
                rightsib=root->parent->c2;
                leftsib=NULL;
            }
            else if(root->parent->c2==root)
            {
                child=1;
                rightsib=root->parent->c3;
                leftsib=root->parent->c1;
            }
            else if(root->parent->c3==root)
            {
                child=2;
                rightsib=root->parent->c4;
                leftsib=root->parent->c2;
            }
            else if(root->parent->c4==root)
            {
                child=3;
                rightsib=NULL;
                leftsib=root->parent->c3;
            }
            
            //check rightsib
            if(rightsib && rightsib->keys[1])
            {
                root->keys[0]=root->parent->keys[child];//overwrite to be deleted key
                root->parent->keys[child]=rightsib->keys[0];
                //leftmost key of irght sib

                //shift sib keys
                rightsib->keys[0]=rightsib->keys[1];
                rightsib->keys[1]=rightsib->keys[2];
                rightsib->keys[2]=0;
            }

            else if(leftsib && leftsib->keys[1])
            {
                root->keys[0]=root->parent->keys[child-1];
                if(leftsib->keys[2]) //if 3 keys
                {
					root->parent->keys[child-1]=leftsib->keys[2];
					leftsib->keys[2]=0;	
				}
                else //if 2 keys
                {
					root->parent->keys[child-1]=leftsib->keys[1];
					leftsib->keys[1]=0;
				}

            }

            else //require merging
            {
                if(child<3 && rightsib)//default merge with rightsib
                {
                    root->keys[0]=root->parent->keys[child];
                    root->keys[1]=rightsib->keys[0];
                    
                    //shift parent keys
                    for(int i=child;i<3;i++)
                    {
                        root->parent->keys[i]=root->parent->keys[i+1];
                    }
                    //shift parent children
                    if(child==0)
                    {
						root->parent->c2=root->parent->c3;
						root->parent->c3=root->parent->c4;
						root->parent->c4=NULL;
					}
					else if(child==1)
					{
						root->parent->c3=root->parent->c4;
						root->parent->c4=NULL;
					}
					else if(child==2)
					{
						root->parent->c4=NULL;
					}

                }

                else //leftsib merge for last child
                {
					leftsib->keys[1]=root->parent->keys[child-1];

					//shift parent keys to left
					for(int i=child-1;i<3;i++)
                    {
                        root->parent->keys[i]=root->parent->keys[i+1];
                    }

					//shift parent children
					if(child==1)
					{
						root->parent->c2=root->parent->c3;
						root->parent->c3=root->parent->c4;
						root->parent->c4=NULL;
					}
					if(child==2)
					{
						root->parent->c3=root->parent->c4;
						root->parent->c4=NULL;
					}
					if(child==3)
					{
						root->parent->c4=NULL;
					}

                }

                //cascade merge check condition
				if(!root->parent->keys[0])
				{
					ttfdelete(root->parent, root->parent->keys[0]);
				}
				
				// //INCLUDE ROOOT UPDATION
				// if(!root->parent)

            }
            
        }
    }

    
    //if internal/root node
        //search predecessor
        //replace with predecessor
        //call delete on the predecessor
    
    else
    {
       predreplace(root, val);
    }

}

int main()
{
	cout<<"----21205006: Ass2 Q4 2-4 TREE INSERTION----\n"<<endl;
	int val=0;

	cout<<"Enter key value: ";
    cin>>val;
	ttfnode *root=newnode(val);
	treeroot=&root;

	cout<<"root: ";
	ttfprint(*treeroot);
	char c='y';
    cout<<"Insert again?";
    cin>>c;

    while(c=='y')
    {
        cout<<"\nEnter key value: ";
        cin>>val;

		cout<<val<<": ";
		insert(searchkey(*treeroot,val),val);
		cout<<"root: ";
		ttfprint(*treeroot);

		cout<<"Insert again?";
        cin>>c;
	}

	cout<<"\nFinal Tree print: \nroot: ";
	ttfprint(*treeroot);

	cout<<"\n\n----21205006: Ass2 Q5 2-4 TREE DELETION----\n"<<endl;
	c='y';
    ttfnode *delnode=NULL;
    while(c=='y')
    {
        cout<<"Enter key to delete: ";
        cin>>val;

		cout<<val<<": ";
		delnode=searchkey(*treeroot,val);
		ttfdelete(delnode,val);

		cout<<"\nTree after deletion: \nroot: ";
		ttfprint(*treeroot);
		cout<<endl;

		cout<<"Delete again?";
        cin>>c;
	}

	cout<<"\nFinal Tree print: \nroot: ";
	ttfprint(*treeroot);

	return 0;
}
