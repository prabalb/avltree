/*
 * wrapper.h
 * Author: Prabal Basu
 * Email: prabalb@aggiemail.usu.edu
 */


/*
 * overload '<<' operator so as to print the output both
 * to the console and to a .txt file whenever required
 */

#include <iostream>
#include <fstream>

using namespace std;

class Output
{
  public:
    std::ofstream outFile;
    Output(const char* fileName) { outFile.open(fileName); }
    ~Output() { outFile.close(); }
};

template<class T>
Output& operator <<(Output& op, T value)
{
  op.outFile << value;
  std::cout << value;
  return op;
};
