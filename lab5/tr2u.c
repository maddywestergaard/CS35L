#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char* argv[]){
  const char* from = argv[1];
  const char* to = argv[2];

  if (strlen(from)!=strlen(to)){
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

  char a;
  int read1 = read(0, &a, 1);
  int write1;

  while(read1>0){
    int i;
    for (i=0; i<strlen(from); i++){
      if (a==from[i]){
        write(1,&to[i],1);
        read1=read(0,&a,1);
        continue;
      }
    }
    write1=write(1,&a,1);
    read1=read(0,&a,1);
  }
  exit(0);
}
