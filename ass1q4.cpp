#include<iostream>
using namespace std;

typedef struct keyValuePair{
    string key;
    string meaning;
    struct keyValuePair *next;
}kvpair;


kvpair* createkvpair(string key, string val)
{
    kvpair* newpair=new kvpair;
    newpair->key=key;
    newpair->meaning=val;
    newpair->next=NULL;

    return newpair;
}

void printDict(kvpair *headiter)
{
    while(headiter!=NULL)
    {
        cout<<headiter->key<<" : ";
        cout<<headiter->meaning<<endl;
        headiter=headiter->next;
    }
}


//print reverse
void reverseLexicalPrintDict(kvpair *headiter)
{
    if(headiter==NULL){
        return;
    }

    reverseLexicalPrintDict(headiter->next);
    cout<<headiter->key<<" : ";
    cout<<headiter->meaning<<endl; 
}


//insert keys
kvpair* insertToDict(kvpair *head, string key, string val)
{
    //search in dict first
    //search till where it should be
    kvpair *iter=head;
    
    //change in head
    if(iter->key>key)
    {
        kvpair *temp=createkvpair(key,val);
        temp->next=iter;
        return temp;
    }

    else{
    //in between nodes
    while(iter->next!=NULL)
    {
        if(iter->key==key)
        {
            cout<<"Key Already Exists"<<endl;
            return head;
        }

        else if(iter->next->key>key)
        break;

        iter=iter->next;
    }

    //last node check 
    //only head check
    if(iter->key==key)
    {
        cout<<"Key Already Exists"<<endl;
        return head;
    }

    //if doesn't exist
    //insert in lexical order
    kvpair *temp=createkvpair(key,val);
    temp->next=iter->next;
    iter->next=temp;
    return head;
    }
}

//delete keys
void deleteFromDict(kvpair *head, string key)
{
    //search for key
    kvpair *iter=head;

    //check if head to be deleted
    // if(head->key==key)
    // {
    //     head=head->next;
    //     return;
    // }

    while(iter!=NULL)
    {
        if(iter->next->key==key)
        {
            iter->next=iter->next->next;
            cout<<"Deleted"<<endl;
            return;
        }

        else
        iter=iter->next;
    }

    cout<<"Key does not exist in Dictionary"<<endl;
}

void updateDict(kvpair *head, string key, string meaning)
{
    //search in dict first
    while(head->key!=key)
    {
        head=head->next;
    }

    if(head==NULL)
    {
        cout<<"Key not found in dict."<<endl;
        return;
    }
    //update meaning
    head->meaning=meaning;
}

// //print alphabetical order
// void lexicalPrintDict(kvpair *head)
// {

// }




int main()
{
    cout<<"-----212005006: Ass1 Q4 Dictionaries-----"<<endl;

    
    string keyword, meaning;
    cout<<"Enter Keyword:";
    cin>>keyword;
    cout<<"Enter meaning: ";
    cin>>meaning;

    kvpair *headpair=createkvpair(keyword, meaning);

    char repeat='y';
    cout<<"Another operation (y/n)? ";
    cin>>repeat;

    while(repeat=='y')
    {
        char c='i';
        cout<<"Enter choice (i/u/d/p/r): ";
        cin>>c;

        switch(c)
        {   
            case 'i':
                
                cout<<"--insert value--"<<endl;
                cout<<"keyword: ";
                cin>>keyword;
                cout<<"meaning: ";
                cin>>meaning;
                headpair=insertToDict(headpair,keyword,meaning);
                break;

            case 'u':
                cout<<"--update value--"<<endl;
                cout<<"keyword: ";
                cin>>keyword;
                cout<<"new meaning: ";
                cin>>meaning;
                updateDict(headpair,keyword,meaning);
                break;

            case 'd':
                cout<<"--delete words--"<<endl;
                cout<<"keyword: ";
                cin>>keyword;
                
                if(headpair->key==keyword)
                {
                    if(headpair->next!=NULL)
                    headpair=headpair->next;
                    else
                    headpair=NULL;
                }
                else
                deleteFromDict(headpair, keyword);
                break;

            case 'p':
                cout << "{"<<endl;
                printDict(headpair);
                cout << "}"<<endl;
                break;

            case 'r':
                cout << "{"<<endl;
                reverseLexicalPrintDict(headpair);
                cout << "}"<<endl;
                break;

            default: 
                cout<<"Enter a valid operation option."<<endl;
                break;
        
        }


        cout<<"Another operation (y/n)? ";
        cin>>repeat;
    }
    
    cout<<"---------by 21205006----------"<<endl;

    return 0;
}