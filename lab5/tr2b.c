#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, const char* argv[]){
  const char* from = argv[1];
  const char* to = argv[2];

  if (strlen(from)!=strlen(to)){
    printf("%d\n", *from);
    printf("%d\n", *to);
    fprintf(stderr, "incompatible from and to");
    exit(1);
  }

  int j,k;
  for (j=0; j<strlen(from); j++){
    for (k=j+1; k<strlen(from); k++){
      if (from[j]==from[k]){
        fprintf(stderr, "duplicate bytes in from");
        exit(1);
      }
    }
  }

  char a = getchar();
  while(a!=EOF){
    int i;
    for (i=0; i<strlen(from); i++){
      if (a==from[i]){
        putchar(to[i]);
        a=getchar();
        continue;
      }
    }
    putchar(a);
    a=getchar();
  }
  exit(0);
}
