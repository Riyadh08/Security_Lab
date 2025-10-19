#include<bits/stdc++.h>
using namespace std;

int main()
{
    string msg;
    cin>>msg;
    string key;
    cin>>key;

    int col = key.size();
    int row = ceil((msg.size() * 1.0)/col);

    char arr[row][col];
    int k=0;
    for(int i=0;i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(k<msg.size()) arr[i][j] = msg[k];
            else arr[i][j] = '*';
            k++;
        }
    }
    cout<<"Matrix (row-wise filled): "<<endl;
    for(int i = 0; i< row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }

    string cipher = "";
    for(int c = 0; c< col; c++)
    {
        int colIdex = (key[c] - '0') - 1;
        for(int r = 0; r< row; r++)
        {
            cipher += arr[r][colIdex];
        }
    }
    cout<<"Cipher Text: "<<cipher<<endl;

    char arr2[row][col];
    int idx = 0;

    for(int c=0; c<col; c++)
    {
        int colIdex = (key[c] - '0') - 1;
        for(int r=0; r<row; r++)
        {
            arr2[r][colIdex] = cipher[idx++];
        }
    }
    cout<<"Matrix after filling cipher: "<<endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout<<arr2[i][j]<<" ";
        }
        cout<<endl;
    }
    string plain = "";
    for(int i=0; i< row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(arr2[i][j] != '*')
                plain += arr2[i][j];
        }
    }

    cout<<"Decryption Plain Text: "<<plain<<endl;
    return 0;
}


/*

ABCDEFGHIJKLMNO
4231

ABCDEFGHIJKLMNO
1234

*/






