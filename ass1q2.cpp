#include<iostream>
#include<stdint.h>
using namespace std;

//linked list
//intersect them
//create a hash table

int hashTableSize=57;
uintptr_t hashTable[57];

typedef struct NODE{
    int value;
    struct NODE *next;
} node;

node* createNode(int val)
{
    node *newnode= (node*)malloc(sizeof(node));
    if(!newnode)
    {
        cout<<"No space";
        exit(0);
    }
    newnode->value=val;
    newnode->next=NULL;
    return newnode;
}

//print linked list
void printLL(node * start)
{
    if(start==NULL)
    {
        cout<<"Empty list";
        return;
    }
    node * temp=start;
    cout<<temp->value<<"(address="<<temp<<")"<<"-->";

    while(temp->next!=NULL)
    {
        cout<<temp->next->value;
        cout<<"(address="<<temp->next<<")"<<"-->";
        temp=temp->next;
    }
    cout<<endl;
}

//hash each element
int hashCheck(node *start){
    node *temp=start;
    bool hashcheck=0;

    while(temp!=NULL)
    {
        uintptr_t hashvalue= reinterpret_cast<uintptr_t>(temp);
        int hash=hashvalue%hashTableSize;
        cout<<"hash key:"<<hash<<" add: "<<hashvalue<<" node value:"<<temp->value;
        if(!hashTable[hash])
        {
            cout<<" new entry to hash table\n";
            hashTable[hash]=hashvalue;
            temp=temp->next;
        }
        else if(hashTable[hash]!=hashvalue) //hash collision & not the same val
        {
            //linear probe
            while(hashTable[hash])
            {
                hash++;
                hash=hash%hashTableSize;
            }
            hashTable[hash]=hashvalue;
            temp=temp->next;
        }
        else
        {
            cout<<" Repeated entry found"<<endl;
            return temp->value;
        }
        
    }
    cout<<endl;
    return 0;

}

int main()
{
    cout<<"-----212005006: Ass1 Q2 Intersection of LL-----"<<endl;

    int val;
    cout<<"----------------LINKED LIST - 1------------"<<endl;
    cout<<"Enter head val:";
    cin>>val;
    node *head1=createNode(val);

    char c='y';
    cout<<"Insert again?";
    cin>>c;
    node *temp1=NULL;

    while(c=='y')
    {
        
        cout<<"Insert data:";
        cin>>val;
        temp1=createNode(val);
        node *temp2=head1;
        while(temp2->next!=NULL)
        {
            temp2=temp2->next;
        }
        temp2->next=temp1;
        cout<<"Insert again?";
        cin>>c;
    }
    printLL(head1);

    cout<<"----------------LINKED LIST - 2------------"<<endl;
    cout<<"Enter head val:";
    cin>>val;
    node *head2=createNode(val);

    c='y';
    cout<<"Insert new node (y) or Insert intersection node (i) :";
    cin>>c;
    node *temp=NULL;

    while(c=='y')
    {
        
        cout<<"Insert data:";
        cin>>val;
        temp=createNode(val);
        node *temp2=head2;
        while(temp2->next!=NULL)
        {
            temp2=temp2->next;
        }
        temp2->next=temp;
        cout<<"Insert new node (y) or Insert intersection node (i):";
        cin>>c;
    }

    if(c=='i')
    {
        cout<<"Insert intersection node value: ";
        cin>>val;

        temp=head1;
        while(temp->value!=val)
        {
            temp=temp->next;
        }

        node *temp2=head2;
        while(temp2->next!=NULL)
        {
            temp2=temp2->next;
        }
        temp2->next=temp;
    }

    printLL(head2);

    //creating intersection point
    cout<<"\n---------Computing hash values---------------\n";
    hashCheck(head1);
    int ipoint=hashCheck(head2);

    if(ipoint)
    cout<<"Intersection at node with value = "<<ipoint<<endl;

    else
    cout<<"No intersection"<<endl;

    cout<<"---------by 21205006----------"<<endl;

    return 0;
}