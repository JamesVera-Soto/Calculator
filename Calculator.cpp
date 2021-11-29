#include "Calculator.h"

string Calculator::reformat(string s){
      string res = "";
      bool changeOccured = false;
      
      for(int i = 0, j = 1; j < s.length(); i++, j++){
          cout << "res: " << res << endl;
          
          // double negatives
          if(s[i] == '-' && s[j] == '-'){
              res += '+';
              i++;
              j++;
              changeOccured = true;
          }
          
          // first number is negative
          else if(i == 0 && s[i] == '-') {
              res += '0';
              res += s[i];
              changeOccured = true;
          }
          
          // multiply from paratheses
          else if(((s[i] >= '0' && s[i] <= '9') || (s[i] == ')' ) || (s[i] == '.')) && s[j] == '('){
              cout << "mfp: " << s[i] << endl;
              res += s[i];
              res += '*';
              changeOccured = true;
          }
          
          else res += s[i];
      }
      res += s[s.length() - 1];
      
      isFormatted = true;
      
      if(changeOccured) return reformat(res);
      cout << "complete reformat: " << res << endl;
      return res;
  }
  
  string Calculator::removeTrailingZeros(string s){
      int i;
      for(i = s.length() -1; i >= 0; i--){
          if(s[i] == '.') break;
          if(s[i] != '0') {
              i++;
              break;
          }
      }
      return s.substr(0, i);
  }
  
  int Calculator::findClosingP(string &s, int l, int r){
      stack<int> pStack;
      while(l < r){
          
          if(s[l] == '(') pStack.push(l);
          
          else if(s[l] == ')') pStack.pop();
          
          if(pStack.empty()) return l;
          
          l++;
      }
      return -1;
  }
  
  string Calculator::getNextNumber(string &s, int &i){
      string curNum = "";
      if(s[0] == '~'){
          i++;
          curNum += '-';
      }
      
      while((s[i] >= '0' && s[i] <= '9') || s[i] == '.'){
          curNum += s[i];
           i++;
      }
      i--;
    return curNum;
  }
  
  double Calculator::plusMinus(string &s, int &i){
      bool numberFound = false;
      string curStr = "";
      while(i < s.length()){
          // number
          if((s[i] >= '0' && s[i] <= '9') || s[i] == '.'){
              numberFound = true;
              curStr += s[i];
              i++;
          }
          // + - operators
          else if(s[i] == '+'){
              // number has already been found
              if(numberFound) {
                  --i;
                  return stod(curStr);
              }
              // no number found yet
              return plusMinus(s, ++i);
          }
          else if(s[i] == '-'){
              // number has already been found
              if(numberFound) {
                  --i;
                  return stod(curStr);
              }
              // no number found yet
              return -plusMinus(s, ++i);
          }
          
          
          // POTENTIAL ERRORS: FIX LATER (include other operators)
          else return stod(curStr);
      }
      return stod(curStr);
  }
  
  double Calculator::opCal(double n1, double n2, char op){
          switch (op){
              case '^': return pow(n1,n2);
              case '*': return n1 * n2;
              case '/': return n1 / n2;
              case '+': return n1 + n2;
              case '-': return n1 - n2;
          }
          return 0.0;
  }
      
  /********** CALCULATE ************/
  string Calculator::calculate(string s){
      cout << "calculate: " << s << endl;
      vector<string> curVec, vec;
      s = reformat(s);
      string curStr = "";
      string prevNum = "";
      string curNum = "";
      char op, ops[] = { '^', '*', '/', '+', '-' };
      
      double n1, n2;
      
      // for paratheses
      for(int i = 0; i < s.length(); i++){
          if(s[i] == '('){
              int len = findClosingP(s,i,s.length()) - i;
              curNum = calculate(s.substr(i+1,len-1));
              curStr += curNum;
              curNum = "";
              i += len;
          }
          else {
              curStr += s[i];
          }
      }

      s = curStr;
      curStr = "";
      for(int i = 0; i < s.length(); i++){
        
      }

      return curStr;
  }