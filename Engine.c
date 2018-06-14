#include "ArrayHandler.c"







void Engine(int count){

  ArrayHandler <int>test(10);
  test.AssignValue(14,0);
  test.PrintArray();
  int * arr = new int[20];
  test.TailArray(arr, 20);
  test.PrintArray();
}
