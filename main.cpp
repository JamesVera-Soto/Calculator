#include "Calculator.h"
using namespace std;

int main()
{
    Calculator cal;
    ofstream outFile("results.txt");
    int MAX = 10;
    string s[MAX];
    string a[MAX];
    
    a[0] = "192.99";
    a[1] = "26";
    a[2] = "0";
    a[3] = "86";
    a[4] = "-11.5";
    a[5] = "15";
    a[6] = "-223.5";
    a[7] = "4097";
    a[8] = "1";
    a[9] = "-99";
    
    s[0] = "(--++--212.99---+++--5-9++-6)";
    s[1] = "3+5*8/2+3";
    s[2] = "0";
    s[3] = "-7+6*2+9^2";
    s[4] = "---15++6/3*0.5+1/2+2";
    s[5] = "6+9";
    s[6] = "-3-((2-5)*6)^2-6/4+0.7(150)";
    s[7] = "(4^2)^(3^(2+1*(-1)))+1";
    s[8] = "1";
    s[9] = "-99";
    
    string res;
    for(int i = 0; i < MAX; i++){
        try{
            res = cal.calculate(s[i]);
            cout << "ANSWER: " << res << endl;
            if(res == a[i]) outFile << "CORRECT! " << res << " for: " << s[i] << endl;
            else outFile << "*** Incorrect *** " << res << " for: " << s[i] << endl;
        }
        catch(...){
            outFile << "!!! ERROR !!! for: " << s[i] << endl;
            cout << "!!! ERROR !!! for: " << s[i] << endl;
            continue;
        }
    }

    return 0;
}