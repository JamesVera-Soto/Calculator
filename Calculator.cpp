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
              if(curNum[0] == '-') curNum[0] = '~';
              i += len;
              curStr += curNum;
              curNum = "";
          }
          else {
              curStr += s[i];
          }
      }
      cout << "post par: " << curStr << endl;
      
      // for cahr ops[] = { '^', '*', '/', '+', '-' } 
      for(int o1 = -1, o2 = 0; o2 < 5; o1+=2, o2+=2){
          bool isTilda = false;
          bool priorityOp = false;
          s = curStr;
          s = reformat(s);
          curStr = "";
          prevNum = "";
          curNum = "";
          for(int i = 0; i < s.length(); i++){
              cout << "come one omg: " << s[i] << " ops " << o1 << o2 << endl;
              // if priority operator
              if((o1 != -1 && s[i] == ops[o1]) || s[i] == ops[o2]){
                  // find next number and result
                  priorityOp = true;
                  op = s[i];
                  i++;
                  prevNum = curNum;
                  curNum = getNextNumber(s, i);
                  cout << "passing to stod: " << prevNum << " and " << curNum << " and op: " << op << " for s: " << s << endl;
                  n1 = stod(prevNum);
                  n2 = stod(curNum);
                  curNum = removeTrailingZeros(to_string(opCal(n1,n2,op)));
                  if(i == s.length() - 1) curStr += curNum;
              }
              else {
                  // number
                  if((s[i] >= '0' && s[i] <= '9') || s[i] == '.' || s[i] == '~'){
                      if(s[i] == '~'){
                          isTilda = true;
                          curNum += '-';
                          i++;
                      }
                      curNum += s[i];
                      if(i == s.length()-1) curStr += curNum;
                  }
                  // other operator
                  else{
                      prevNum = curNum;
                      if(isTilda && !priorityOp){
                        isTilda = false;
                        prevNum[0] = '~';
                      }
                      curStr += prevNum;
                      curStr += s[i];
                      curNum = "";
                  }
                  cout << s[i] << endl;
              }
          }
      }
      
      return curStr;
  }