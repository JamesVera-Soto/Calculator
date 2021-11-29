#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <math.h>
#include <vector>
#include "Calculator.h"
using namespace std;


int main()
{
    ofstream outFile("results.txt");
    int MAX = 10;
    string s[MAX];
    string a[MAX];
    
    a[0] = "-223.5";
    a[1] = "1870.5";
    a[2] = "22";
    a[3] = "27";
    a[4] = "10";
    a[5] = "0";
    a[6] = "-4";
    a[7] = "26";
    a[8] = "25";
    a[9] = "8";
    
    s[0] = "-3-((2-5)*6)^2-6/4+0.7(150)"; // -223.5 => 424.5 ***INCORRECT***
    
    s[1] = "3+((2+5)*6)^2-6/4+0.7(150)"; // 1870.5 => CORRECT
    s[2]= "5+((3+5)*2)+1"; // 22 => CORRECT
    s[3] = "2+5^2"; // 27 => CORRECT
    s[4] = "2(((5)))"; // 10 => CORRECT
    s[5] = "0"; // 0 => CORRECT
    s[6] = "1---5"; // -4 => CORRECT
    
    s[7] = "1+(-5)^2"; // -24 => 26 ***INCORRECT***
    s[8] = "(-5)(-5)"; // 25 => ERROR INVALID_ARGUMENT stod 0-5*-5
    
    s[9] = "2(4)";
    
    
    Calculator cal;
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
            continue;
        }
    }

    return 0;
}