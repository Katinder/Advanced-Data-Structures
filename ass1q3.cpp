#include<iostream>
using namespace std;

//linked list
//make it cyclic
//create a hash table

int hashTableSize=57;
int hashTable[57];

int hashFunction(int val)
{
    int hash=val%hashTableSize;

    return hash;
}

//hash each element
void hashCheck(int *arr, int k){
   
    //find just greater prime number than k

    for(int i=0;i<k;i++)
    {
        int hashKey=hashFunction(arr[i]);
        
        if(!hashTable[hashKey])
        {
            hashTable[hashKey]=arr[i];
        }

        else if(hashTable[hashKey]!=arr[i])
        {
            cout<<"hash collision: using linear probing";

            while(hashTable[hashKey])
            {
                hashKey++;
            }
            hashTable[hashKey]=arr[i];
        }
        else
        {
            cout<<"Duplicate found: "<<arr[i]<<endl;
        }

    }

}

int main()
{
    cout<<"----212005006: Ass1 Q3 Duplicate Values in Array----"<<endl;

    int aSize=0;
    cout<<"Array size: ";
    cin>>aSize;

    int *arr=new int(aSize);
    int val=0;

    cout<<"----------------Enter array values------------"<<endl;
    for(int i=0;i<aSize;i++)
    {
        cout<<"Val["<<i<<"]:";
        cin>>arr[i];
    }

    int k=0;
    cout<<"Value of k:";
    cin>>k;


    cout<<"---------Duplicates----------"<<endl;
    if(k<aSize)
    {
            //hash till k
            hashCheck(arr,k);
    }
    else
    {
            //hash all
            hashCheck(arr,aSize);
    }

    cout<<"---------by 21205006----------"<<endl;

    return 0;
}