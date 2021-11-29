#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

string reformat(string s){
    string res = "";
    bool changeOccured = false;
    
    for(int i = 0, j = 1; j < s.length(); i++, j++){
        
        // multiply from paratheses
        if(((s[i] >= '0' && s[i] <= '9') || (s[i] == ')' ) || (s[i] == '.')) && s[j] == '('){
            res += s[i];
            res += '*';
            changeOccured = true;
        }
        
        else res += s[i];
    }
    res += s[s.length() - 1];
    
    if(changeOccured) return reformat(res);
    //cout << "Complete reformat: " << res << endl;
    return res;
}

string removeTrailingZeros(string &s){
    int i;
    bool dotted = false;
    for(i = 0; i < s.length(); i++){
        if(s[i] == '.') dotted = true;
    }
    if(dotted){
        for(i = s.length() -1; i >= 0; i--){
            if(s[i] == '.') break;
            if(s[i] != '0') {
                i++;
                break;
            }
        }
        return s.substr(0, i);
    }
    return s;
}

int findClosingP(string &s, int l, int r){
    stack<int> pStack;
    while(l < r){
        
        if(s[l] == '(') pStack.push(l);
        
        else if(s[l] == ')') pStack.pop();
        
        if(pStack.empty()) return l;
        
        l++;
    }
    return -1;
}

double plusMinus(vector<string> v, int &i){
    bool numberFound = false;
    string curStr = "";
    while(i < v.size()){
        // number will be digit or len > 1
        if(v[i].length() > 1 || isdigit(v[i][0])){
            numberFound = true;
            curStr += v[i];
            i++;
        }
        // + - operators
        else if(v[i] == "+"){
            // number has already been found
            if(numberFound) {
                --i;
                return stod(curStr);
            }
            // no number found yet
            return plusMinus(v, ++i);
        }
        else if(v[i] == "-"){
            // number has already been found
            if(numberFound) {
                --i;
                return stod(curStr);
            }
            // no number found yet
            return -plusMinus(v, ++i);
        }
        // POTENTIAL ERRORS: FIX LATER
        else return stod(curStr);
    }
    return stod(curStr);
}

void displayV(vector<string> v){
    for(int i = 0; i < v.size(); i++){
        cout << "i: " << i << " s: " << v[i] << endl;
    }
}

/******** CALCULATE *********/
string calculate(string s){
    s = reformat(s);
    vector<string> curVec, prevVec;
    string prevNum = "";
    string curNum = "";
    string sc;
    double n1, n2;
    
    
    // Recursive calls for parantheses
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '('){
            int len = findClosingP(s,i,s.length()) - i;
            curNum = calculate(s.substr(i+1,len-1));
            curVec.push_back(curNum);
            curNum = "";
            i += len;
        }        
        else if(isdigit(s[i]) || s[i] == '.') {
            curNum += s[i];
            if(i == s.length()-1) {
                curVec.push_back(curNum);
            }
        }
        else {
            if(curNum.length() != 0) {
                curVec.push_back(curNum);
                curNum = "";
            }
            sc = s[i];
            curVec.push_back(sc);
        }
    }
    
    // Go through vec for power
    prevVec = curVec;
    curVec.clear();
    curNum = ""; 
    for(int i = 0; i < prevVec.size(); i++){
        // index is a number
        if(prevVec[i].length() > 1 || isdigit(prevVec[i][0])){
            curNum = prevVec[i];
        }
        
        // or index is a priority operator
        else if(prevVec[i] == "^"){
            // operator ^
            n1 = pow(stod(curNum), stod(prevVec[i+1]));
            i++;
            curNum = to_string(n1);
        }
        
        // or index is non-priority operator
        else {
            // update curVec
            if(curNum.length() != 0) curVec.push_back(curNum);
            curNum = "";
            curVec.push_back(prevVec[i]);
        }
    }
    curVec.push_back(curNum);
    
    // Go through vec for multiply divide
    prevVec = curVec;
    curVec.clear();
    curNum = "";
    for(int i = 0; i < prevVec.size(); i++){
        // index is a number
        if(prevVec[i].length() > 1 || isdigit(prevVec[i][0])){
            curNum = prevVec[i];
        }
        
        // or index is a priority operator
        else if(prevVec[i] == "*" || prevVec[i] == "/"){
            // operator *
            if(prevVec[i] == "*") n1 = stod(curNum) * stod(prevVec[i+1]);
            // operator /
            else if(prevVec[i] == "/") n1 = stod(curNum) / stod(prevVec[i+1]);
            i++;
            curNum = to_string(n1);
        }
        
        // or index is non-priority operator
        else {
            // update curVec
            if(curNum.length() != 0) curVec.push_back(curNum);
            curNum = "";
            curVec.push_back(prevVec[i]);
        }
    }
    curVec.push_back(curNum); 
    
    // Go through vec for plus minus
    prevVec = curVec;
    curVec.clear();
    curNum = "0";
    for(int i = 0; i < prevVec.size(); i++){
        // index is number
        if(prevVec[i].length() > 1 || isdigit(prevVec[i][0])){
            curNum = prevVec[i];
        }
        
        else {
            // or index is operator +
            if(prevVec[i] == "+") n1 = stod(curNum) + plusMinus(prevVec, ++i);
            
            // or index is operator -
            else if(prevVec[i] == "-") n1 = stod(curNum) - plusMinus(prevVec, ++i);
            curNum = to_string(n1);
        }
        
    }
        
    return removeTrailingZeros(curNum);
}


int main()
{
    ofstream outFile("results.txt");
    int MAX = 7;
    string s[MAX];
    string a[MAX];
    
    a[0] = "192.99";
    a[1] = "26";
    a[2] = "0";
    a[3] = "86";
    a[4] = "-11.5";
    a[5] = "15";
    a[6] = "-223.5";
    
    s[0] = "(--++--212.99---+++--5-9++-6)";
    s[1] = "3+5*8/2+3";
    s[2] = "0";
    s[3] = "-7+6*2+9^2";
    s[4] = "---15++6/3*0.5+1/2+2";
    s[5] = "6+9";
    s[6] = "-3-((2-5)*6)^2-6/4+0.7(150)";
        
    
    
    string res;
    for(int i = 0; i < MAX; i++){
        try{
            res = calculate(s[i]);
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