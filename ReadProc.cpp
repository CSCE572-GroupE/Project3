#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

const string IFNAME = "wlan0";

int main()
{
    ifstream input("/proc/net/wireless");
    if(!input)
    {
        cout << "Couldn't open the file\n";
        return 1;
    }

    string line;
    while(getline(input, line)) {
        istringstream bp(line);
        string fname;
        bp >> fname;
        if(fname == IFNAME + ':')
        {
            replace(line.begin(), line.end(), '.', ' ');
            cout << "first word: " << fname << '\n';
            string word;
            while(bp >> word)
                cout << "next word: " << word << '\n';
        }
    }
}
