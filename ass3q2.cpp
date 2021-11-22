#include<iostream>
#include<vector>
using namespace std;

int r[256]; //right most occurence of character

//bad character rule
void calcBadCharArray(string pat, int patSize)
{
    for(int i=0;i<256;i++)
    {
        r[i]=-1;
    }

    for(int i=0;i<patSize;i++)
    {
        r[(int) pat[i]]=i;
    }
}

int main()
{

    cout<<"------21205006: Ass3 Q2 Boyer-Moore Pattern Matching-------\n"<<endl;

    string text="this is a good place to have a good start";
    string pattern="good";
    vector<int> matches;

    int n=text.length();
    int m=pattern.length();
    cout<<text<<endl<<pattern<<endl;
    calcBadCharArray(pattern, m);
    int foundflag=0;

    int i=m-1,j=m-1;
    int oldshift=0, shift=0;
    while(shift<n-m) //pat length < text length always
    {
        
        if(pattern[j]==text[shift+j])
        {
            if(j==0)
            {
                //complete match
                foundflag=1;
                cout<<"MATCH FOUND AT i= "<<shift<<endl;
                matches.push_back(shift);

                cout<<text<<endl;
                for(int k=0;k<shift;k++)
                {
                    cout<<" ";
                }
                cout<<pattern<<endl;

                shift+=1;
                
                cout<<"New shift: "<<shift<<" comparing "<<text[shift+j]<<" and "<<pattern[m-1]<<endl;
                continue;
            }
            else{
                i--;
                j--;
            }
        }
        else
        {
            shift=shift+max(1,j-r[(int)text[shift+j]]);
            cout<<"New shift: "<<shift<<" comparing "<<text[shift+j]<<" and "<<pattern[m-1]<<endl;
            j=m-1; //start from right always
        }
    }
    if(!foundflag)
    {
        cout<<"No Match found";
    }
    else{

        cout<<"\nMatched indices: {";
        for(auto a=matches.begin();a!=matches.end();++a)
        {
            cout<<*a<<",";
        }
        cout<<"\b}\n";
    }
    
}
