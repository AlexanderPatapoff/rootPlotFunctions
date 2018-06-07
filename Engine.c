#include "ArrayHandler.c"







void Engine(int count){

  ArrayHandler <int>test(10);
  test.AssignValue(14,0);
  cout << test.GetValue(0) << endl;
}
