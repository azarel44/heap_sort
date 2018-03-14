#include <iostream>
#include "cmpt_error.h"
#include "heapsort.h"

using namespace std;

int main() {
  vector<int> basevector = {5, 9, 20, 3, 1, 22, 11, 6};
  int iterate = 0;
  int size = basevector.size();
  PQ_heap queue;
  while (iterate < size)
  {
    queue.insert(basevector.at(iterate));
    iterate++;
  }
  queue.print();
  cout << endl;
  queue.pq_sort();
  queue.print();
  return 0;
}