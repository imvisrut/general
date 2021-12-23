#include <bits/stdc++.h>

using namespace std;

void print(vector<vector<char>> v)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }
}

vector<int> getDimension(vector<vector<char>> v, char c)
{
    if(c=='J')
        c='I';
    vector<int> d;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(c == v[i][j])
            {
                d.push_back(i);
                d.push_back(j);
            }
        }
    }
    
    return d;
}

string encrypt_playfair_ciper(string s, vector<vector<char>> v)
{
    string encrypt="";
    
    for(int i=0;i<s.length();i=i+2)
    {
        char first=s[i];
        char second=s[i+1];
        
        // cout<<first<<" "<<second<<endl;
        
        vector<int> dimension=getDimension(v,first-97+65);
        int u1=dimension[0];
        int v1=dimension[1];
        
        // cout<<"u1="<<u1<<" v1="<<v1<<endl;
        
        dimension=getDimension(v,second-97+65);
        int u2=dimension[0];
        int v2=dimension[1];
        
        // cout<<"u2="<<u2<<" v2="<<v2<<endl;
        
        if(u1==u2 && v1!=v2)
        {
            int s=(v1+1)%5;
            int t=(v2+1)%5;
            
            encrypt+=v[u1][s];
            encrypt+=v[u1][t];
        }
        else if(u1!=u2 && v1==v2)
        {
            int s=(u1+1)%5;
            int t=(u2+1)%5;
            
            encrypt+=v[s][v1];
            encrypt+=v[t][v1];
        }
        else
        {
            encrypt+=v[u1][v2];
            encrypt+=v[u2][v1];
        }
    }
    
    return encrypt;
}

int main()
{
    string key,s;
    key="MONARCHY";
    s="givememore";
    // cout<<"Enter key:-";
    // cin>>key;
    // cout<<"Enter string:-";
    // cin>>s;
    
    vector<vector<char>> v(5,vector<char>(5,0));
    
    int temp=0;
    
    int i,j;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(temp<key.length())
            {
                v[i][j]=key[temp];
                temp++;
            }
            else
                break;
        }
        
        if(temp>=key.length())
            break;
    }
    
    // cout<<"i="<<i<<" j="<<j<<endl;
    
    string temp_str="";
    for(int k=0;k<26;k++)
    {
        char c=65+k;
        if(key.find(c) != string::npos) //character present in KEY
        {
            continue;
        }
        else
        {
            temp_str+=c;
        }
    }
    
    // cout<<"temp-str="<<temp_str<<endl;
    temp=0;
    
    for(;i<5;i++)
    {
        for(;j<5;j++)
        {
            if(temp_str[temp]!='J')
                v[i][j]=temp_str[temp];
            else
                j--;    //because it waste 1 j iteration
            temp++;
        }
        
        j=0;
    }
    
    print(v);
    
    string encrypt=encrypt_playfair_ciper(s,v);
    cout<<encrypt<<endl;

    return 0;
}
