#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
int max(int a, int b);
static long calls = 0; 
static int** memo = NULL;
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( char *X, char *Y, int m, int n )
{
    if(memo[m][n] != -1) return memo[m][n];
    ++calls;
   if (m == 0 || n == 0)
   {memo[m][n] = 0; return memo[m][n];}

   if (X[m-1] == Y[n-1])
   {memo[m][n] = 1 + lcs(X, Y, m-1, n-1); return memo[m][n]; }
   else
   {memo[m][n] = max(lcs(X, Y, m, n-1), lcs(X, Y, m-1, n)); return memo[m][n];}
}
 
/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Driver program to test above function */
int main()
{
  char X[] = "AGGTAB";
  char Y[] = "GXTXAYB";
 
  int m = strlen(X);
  int n = strlen(Y);
  memo = new int*[m+1];
  for(int i =0; i<=m; ++i)
  {
      memo[i] = new int[n+1];
      for(int j =0; j <= n; ++j)
      {
          memo[i][j] = -1;
      }
  }

  int result = lcs(X,Y,m,n);
  printf("Length of LCS is %d, calls = %ld\n", result, calls );
 
  return 0;
}
