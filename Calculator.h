#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Calculator{
private:
  bool isFormatted = false;

public:

  string reformat(string s);

  string removeTrailingZeros(string s);

  int findClosingP(string &s, int l, int r);

  string getNextNumber(string &s, int &i);

  double plusMinus(string &s, int &i);

  double opCal(double n1, double n2, char op);

  string calculate(string s);

};