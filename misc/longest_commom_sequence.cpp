#include <iostream>
#include <vector>
#define N 1000
using namespace std;

vector<vector<int>> memo (N, vector<int>(N, -1));

int lcs_bottomup(const string& p, const string& q, const int n, const int m) {
   for(int i=0; i<=n; i++){
      for(int j=0; j<=m and memo[i][j] == -1; j++){
         if(i == 0 or j == 0)
            memo[i][j] = 0;
         else if(p[i-1] == q[j-1])
            memo[i][j] = 1 + memo[i-1][j-1];
         else
            memo[i][j] = max(memo[i-1][j], memo[i][j-1]);
      }
   }
   return memo[n][m];
}


int lcs(const string& p, const string& q, int n, int m){
   if(memo[n][m] != -1)
      return memo[n][m];
   if(n == 0 or m == 0){
      memo[n][m] = 0;
   }
   else if(p[n-1] == q[m-1]) {
      memo[n][m] = 1 + lcs(p, q, n-1, m-1);
   }
   else {
      memo[n][m] = max(lcs(p, q, n-1, m), lcs(p, q, n, m-1));
   }
   return memo[n][m];
}

int main() {
   string k = "AACDACASDADASDCASDASAHUDHAUSHIASDJIACASIJDOXKCZJOJDOSAJ";
   string m = "BBACKASUASHDUASHDQUWIEQWIHDIHCJKNJKZHASIDHAUSJHEIAEIOJASDASIJDIASEQEJIQEIWJIODASK";
   cout << lcs_bottomup(k, m, k.size(), m.size()) << endl;
   return 0;
}
