#include <bits/stdc++.h>

using namespace std;
#define vr 6

int TSP(int grph[][vr], int p) {// implement traveling Salesman Problem. 
    vector<int> ver; //
   for (int i = 0; i < vr; i++)
      if (i != p)
         ver.push_back(i);
    int m_p = INT_MAX; // store minimum weight of a graph
   do {
      int cur_pth = 0;
      int k = p;
      for (int i = 0; i < ver.size(); i++) {
         cur_pth += grph[k][ver[i]];
         k = ver[i];
      }
      cur_pth += grph[k][p];
      m_p = min(m_p, cur_pth); // to update the value of minimum weight
   }
   while (next_permutation(ver.begin(), ver.end()));
   return m_p;
}
int main() {
   int grph[][vr] = { { 0, 5, 10, 15 }, //values of a graph in a form of matrix
      { 5, 0, 20, 30 },
      { 10, 20, 0, 35 },
      { 15, 30, 35, 0 }
   };
   int grph2[][vr] = {
       
{-1, 79, 14, 11, 14, 20},
{30, -1, 10, 14, 20, 34},
{12, 20, -1, 10, 22, 50},
{16, 12, 15, -1, 14, 72},
{15, 42, 32, 24, -1, 28},
{50, 81, 60, 52, 38, -1}
   };
   int p = 0;
   double S,E;
   S = clock();
   cout<< "\n The result is: "<< TSP(grph2, p) << endl;
   E = clock();
   cout << (E-S)/ CLOCKS_PER_SEC;
   return 0;
}