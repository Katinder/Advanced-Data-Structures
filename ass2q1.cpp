//Creation Insertion RBtree

#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct treeNode{
    int value;
    char color; //r or b
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* parent;
}rbnode;

rbnode* lastinsert=NULL;

//create new node
rbnode * createNode(int val)
{

    rbnode* newnode=(rbnode*)malloc(sizeof(rbnode));
    newnode->value=val;
    newnode->left=NULL;
    newnode->right= NULL;
    newnode->parent=NULL;
    newnode->color='R';
    return newnode;
}

//left rotate function
void slr(rbnode* rotator, rbnode** root)
{
    rbnode *proot=rotator->parent;
    rbnode *rchild=rotator->right;
    rbnode *lrchild=rchild->left;

    rchild->left=rotator;
    rotator->parent=rchild;

    rotator->right=lrchild;
    if(lrchild!=NULL)
    lrchild->parent=rotator;


    if(proot!=NULL)
    {
        rchild->parent=proot;

        if(proot->left==rotator)
        proot->left=rchild;

        else if(proot->right==rotator)
        proot->right=rchild;
    }

    if(proot==NULL) //if change in root node
    {
        *root=rchild;
        rchild->parent=NULL;
    }

}

//right rotate function
void srr(rbnode* rotator, rbnode** root)
{
    rbnode * proot=rotator->parent;
	rbnode* lchild=rotator->left;
	rbnode * rlchild=lchild->right;

	lchild->right=rotator;
	rotator->parent=lchild;

	rotator->left=rlchild;
	if(rlchild!=NULL)
	rlchild->parent=rotator;
	
	if(proot!=NULL)
	{
        lchild->parent=proot;

		if(proot->left==rotator)
		proot->left=lchild;
		
		else if(proot->right==rotator)
		proot->right=lchild;
	}

    if(proot==NULL) //change in root node
    {
        *root=lchild;
        lchild->parent=NULL;
    }
}

//rb insert
rbnode* insert(rbnode *root, int val)
{
    if(root==NULL)
    {
        lastinsert=createNode(val);
        return lastinsert;
    }
    if(root->value==val)
    {
        cout<<"Key already exists"<<endl;
        return root;
    }
    else if(root->value > val)
    {
        root->left=insert(root->left, val);
        root->left->parent=root;
    }
    else if(root->value < val)
    {
        root->right=insert(root->right, val);
        root->right->parent=root;
    }
    return root;
}

//fix the double red nodes
void doubleRedFix(rbnode* problemnode, rbnode** treeroot)
{
    //when we reach to root node after iterating
    if(problemnode->parent==NULL) 
    {
        problemnode->color='B';
        return;
    }

    else if(problemnode->parent->color=='B')
    {
        return;
    }

    //if parent is red
    else if(problemnode->parent->color=='R')
    {
        //if parent is on left of grandparent
        //uncle will be on right
        if(problemnode->parent==problemnode->parent->parent->left)
        {
            //CASE1: uncle iexists and is red 
                //only need to recolor
            if(problemnode->parent->parent->right && problemnode->parent->parent->right->color=='R')
            {
                problemnode->parent->color='B';
                problemnode->parent->parent->color='R'; //gp red
                problemnode->parent->parent->right->color='B'; //unlce black
                // //move to gp for double red check
                // lastinsert=problemnode->parent->parent;
                return;
            }
            //CASE2: unlce is black
                //check if line or triangle form
            else if(problemnode->parent->parent->right==NULL || problemnode->parent->parent->right->color=='B')
            {
                //if line form
                if(problemnode==problemnode->parent->left)
                {
                    //single right rotation
                    //pg color change
                    problemnode->parent->color='B';
                    problemnode->parent->parent->color='R';
                    srr(problemnode->parent->parent, treeroot);
                    return;
                }

                //triangle form
                else if(problemnode==problemnode->parent->right)
                {
                    //double rot
                    //left then right
                    //Ng color change
                    problemnode->color='B';
                    problemnode->parent->parent->color='R';
                    rbnode *gp=problemnode->parent->parent;
                    slr(problemnode->parent, treeroot);
                    srr(gp, treeroot);
                    return;
                }
            }
        }

        //if parent lie on right of gp
        //uncle is on left
        else if(problemnode->parent==problemnode->parent->parent->right)
        {
            //CASE1: uncle red
            //only need to recolor
            if(problemnode->parent->parent->left && problemnode->parent->parent->left->color=='R')
            {
                problemnode->parent->color='B';
                problemnode->parent->parent->color='R'; //gp red
                problemnode->parent->parent->left->color='B'; //unlce black
                return;
            }
            //CASE2: unlce is black
                //check if line or triangle form
            else if(problemnode->parent->parent->left==NULL || problemnode->parent->parent->left->color=='B')
            {
                //if line form
                if(problemnode==problemnode->parent->right)
                {
                    //single right rotation
                    //pg color change
                    problemnode->parent->color='B';
                    problemnode->parent->parent->color='R';
                    slr(problemnode->parent->parent, treeroot);
                    return;
                }

                //triangle form
                else if(problemnode==problemnode->parent->left)
                {
                    //double rot
                    //left then right
                    //Ng color change
                    problemnode->color='B';
                    problemnode->parent->parent->color='R';
                    rbnode *gp=problemnode->parent->parent;
                    srr(problemnode->parent, treeroot);
                    slr(gp, treeroot);
                    return;
                }
            }
        }
    }
}

rbnode** insertnfix(rbnode* root, int val)
{
    root=insert(root, val);

    //iteratively check if double red violation exists
    while((lastinsert!=root) && (lastinsert->color=='R') && (lastinsert->parent->color=='R'))
    {
        doubleRedFix(lastinsert, &root);
        //move to upper node 
        //and check for double red problem
        if(lastinsert->parent)
        lastinsert=lastinsert->parent;
    }
    if(lastinsert!=root)
    {
        while(lastinsert!=root)
        {
            lastinsert=lastinsert->parent;
            //check if gp vali problem
            if(lastinsert->color=='R' && lastinsert->parent)
            {
                if(lastinsert->parent->color=='R')
                doubleRedFix(lastinsert, &root);
            }
        }
        
    }
    if(lastinsert==root && lastinsert->color=='R')
    {
        lastinsert->color='B';
    }

    return &lastinsert;
}

void inorder(rbnode * root)
{
	if(root==NULL)
	return;
	
	inorder(root->left);
	cout<<root->value<<" c= "<<root->color<<" p= ";
	if(root->parent!=NULL) cout<<root->parent->value<<endl;
	else cout<<"NULL\n";
	inorder(root->right);
	
}

void postorder(rbnode * root)
{
	if(root==NULL)
	return;
	
	postorder(root->left);
	postorder(root->right);
	cout<<root->value<<" c= "<<root->color<<" p= ";
	if(root->parent!=NULL) cout<<root->parent->value<<endl;
	else cout<<"NULL\n";
	
}

void preorder(rbnode * root)
{
	if(root==NULL)
	return;
	
	cout<<root->value<<" c= "<<root->color<<" p= ";
	if(root->parent!=NULL) cout<<root->parent->value<<endl;
	else cout<<"NULL\n";
	preorder(root->left);
	preorder(root->right);
		
}

void rbtsearch(rbnode* root, int key)
{
    if(root==NULL)
    {
        cout<<"Key not found";
        return;
    }

    else if(root->value==key)
    {
        cout<<"Key found: Value="<<root->value;
        cout<<" color: "<<root->color;
        if(root->parent)
        cout<<" parent: "<<root->parent->value<<endl;
        else
        cout<<" root node"<<endl;
        return;  
    }

    else if(key > root->value)
        rbtsearch(root->right, key);
    
    else
        rbtsearch(root->left, key);

    return;
}

int main()
{
    cout<<"----21205006: Ass2 Q1 RBTREE INSERTION----"<<endl;
    int val=0;

    rbnode *root=NULL;
    rbnode **treeroot=NULL;
    cout<<"Enter key value: ";
    cin>>val;
    root=createNode(val);
    treeroot=&root;
    root->color='B';

    char c='y';
    cout<<"Insert again?";
    cin>>c;

    while(c=='y')
    {
        cout<<"Enter key value: ";
        cin>>val;

        treeroot=insertnfix(*treeroot,val);
        cout<<"Insert again?";
        cin>>c;
    }
    

    cout<<"----21205006: Ass2 Q2 RBTREE SEARCHING----"<<endl;
    int key=0;
    c='y';
    while(c=='y')
    {
        cout<<"Enter key to search: ";
        cin>>key;
        rbtsearch(*treeroot, key);

        cout<<"Search another key?";
        cin>>c;
    }
    cout<<endl;

    cout<<"----21205006: Ass2 Q3 RBTREE TRAVERSAL----"<<endl;
    cout<<"Inorder Traversal "<<endl;
    inorder(*treeroot);
    cout<<"Preorder Traversal"<<endl;
    preorder(*treeroot);
    cout<<"Postorder Traversal"<<endl;
    postorder(*treeroot);

    return 0;
}