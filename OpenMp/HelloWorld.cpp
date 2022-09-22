#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

int main() {
#pragma omp parallel 
  {
    cout << "\nHello from PRN 2019BTECS00033 with thread "
         << omp_get_thread_num();
  }
  return 0;
}