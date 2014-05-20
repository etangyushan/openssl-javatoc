#include <stdio.h>
#include <string.h>

int main()
{
   char arr[5][5]={};
   strcpy(arr[1], "hahah");
   strcpy(arr[2], "hahah");
   strcpy(arr[3], "hahah");
   int res = sizeof(arr);
   printf ("%d\n", res);
}
