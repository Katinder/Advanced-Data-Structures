#include<iostream>
using namespace std;

int main()
{

    cout<<"------21205006: Ass3 Q1 LCS-------\n"<<endl;

    string s1="ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    string s2="GTCGTTCGGAATGCCGTTGCTCTGTAAA";

    int m=s1.length();
    int n=s2.length();

    int lcs[m + 1][n + 1]; 

     for(int i=0;i<=m;i++) 
    { 
        for(int j=0;j<=n;j++) 
        { 
            if(i==0) //first row
                lcs[i][j] = 0; 
            
            if(j==0) //first col
                lcs[i][j]=0; 
        }
    }

    for(int i=1;i<=m;i++) 
    { 
        for(int j=1;j<=n;j++) 
        { 
            if(s1[i-1]==s2[j-1]) //if same character
                //diagonal + 1
                lcs[i][j]=lcs[i-1][j-1]+1; 
    
            else
            {
                // same as upper cell value
                if(lcs[i-1][j]>lcs[i][j-1])
                    lcs[i][j]=lcs[i-1][j];

                //same as left cell value
                else 
                    lcs[i][j]=lcs[i][j-1];
            }
        }
    }

    cout<<"String1: "<<s1<<"\nString2: "<<s2<<endl;
    cout<<"Length of the longest common substring: "<<lcs[m][n]<<endl;
}