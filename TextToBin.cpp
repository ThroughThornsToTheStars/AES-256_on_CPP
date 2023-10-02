#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
using namespace std;

string f(int d_code)
{
    string b_code;
    int b = 0;
    int q = 0;
    
    if (d_code != 0)
    {
        while (true)
        {
            q = d_code / 2;
            if (q == 0) 
            {
                b_code.insert(b_code.begin(), '1');
                break;
            }
            b = d_code % 2;
            if (b == 0) b_code.insert(b_code.begin(), '0');
            if (b == 1) b_code.insert(b_code.begin(), '1');
            d_code = q;
        }
    }
    else b_code.insert(b_code.begin(), '0');
    
    int c = (b_code.size() % 4);
    if (c != 0)
        for (int i = 0; i < 4 - c; i++)
            b_code.insert(b_code.begin(),'0');
    else
    {
        if (b_code.size() == 4)
            for (int i = 0; i < 4; i++)
                b_code.insert(b_code.begin(),'0');
    }
    
    return b_code;
}
 
 
int main()
{
    setlocale(LC_ALL, "Russian");
    string filePath;
    cout << "Enter the file path: ";
    cin >> filePath;

    ifstream fin(filePath, ios::binary);
    if (!fin)
    {
        cout << "Error when opening the file!" << endl;
        return 1;
    }

    ofstream MyFile("input.bin", ios::binary);
    string str((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    for (int i = 0; i < str.size(); ++i)
    {
        string binary_code = f((int)str[i]);
        MyFile.write(binary_code.c_str(), binary_code.size());
    }
    return 0;
}