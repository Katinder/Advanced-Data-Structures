#include<iostream>
#include<stdint.h>
using namespace std;

//linked list
//make it cyclic
//create a hash table

int hashTableSize=23;
uintptr_t hashTable[23];

//defining a node
typedef struct NODE{
    int value;
    struct NODE *next;
} node;

//allocate memory, assign value
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

//print linked list before its circular
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
    cout<<"Null"<<endl;
}

//iterate LL & hash each element until loop found
bool hashCheck(node *start){
    node *temp=start;
    bool hashcheck=0;

    while(temp!=NULL)
    {
        uintptr_t hashvalue= reinterpret_cast<uintptr_t>(temp);
        int hash=hashvalue%hashTableSize;
        cout<<"add: "<<hashvalue<<" value:"<<temp->value<<" hash:"<<hash;
        if(!hashTable[hash])
        {
            cout<<" new entry to hash table\n";
            hashTable[hash]=hashvalue;
            temp=temp->next;
        }
        else if(hashTable[hash]!=hashvalue) //hash collision & not the same val
        {
            //linear prob
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
            cout<<"Repeated entry found"<<endl;
            return true;
        }
        
    }
    cout<<endl;
    return false;

}

int main()
{
    cout<<"-----212005006: Ass1 Q1 Circular LL-----"<<endl;

    int val;
    cout<<"Enter head val:";
    cin>>val;
    node *head=createNode(val);

    char c='y';
    cout<<"Insert again?";
    cin>>c;
    node *temp=NULL;

    while(c=='y')
    {
        
        cout<<"Insert data:";
        cin>>val;
        temp=createNode(val);
        node *temp2=head;
        while(temp2->next!=NULL)
        {
            temp2=temp2->next;
        }
        temp2->next=temp;
        cout<<"Insert again?";
        cin>>c;
    }
    cout<<"Linked list without the loop:"<<endl;
    printLL(head);
    cout<<endl;

    //add a loop manually
    head->next->next->next->next=head->next;

    if(hashCheck(head))
    cout<<"LOOP PRESENT. CYCLIC."<<endl;

    else
    cout<<"NO LOOP. NOT CYCLIC."<<endl;

    cout<<"---------by 21205006----------"<<endl;

    return 0;
}