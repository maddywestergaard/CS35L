#include <stdlib.h>
#include <stdio.h>


int frobcmp(char const *a, char const *b)
{
  int aindex = 0;
  int bindex = 0;
  while(a[aindex] != ' ' && b[bindex] != ' '){
    if((a[aindex]^0x2A) > (b[bindex]^0x2A))
      return 1;
    else if((b[bindex]^0x2A) > (a[aindex]^0x2A))
      return -1;
    aindex++;
    bindex++;
  }

  if (a[aindex]==' ' && b[bindex]==' ')
    return 0;
  else if (a[aindex]!=' ' && b[bindex]==' ')
    return 1;
  else
    return -1;
}

int cmp(const void *a, const void *b){
  return frobcmp(*(const char**) a, *(const char**) b);  
}

void checkerrorinput()
{
  if (ferror(stdin)){
    fprintf(stderr, "input error");
    exit(1);
  }
}

void checkerrorout()
{
  if (ferror(stdout)){
    fprintf(stderr, "output error");
    exit(1);
  }
}


int main(void)
{
  char** lines = (char**)malloc(sizeof(char*));

  int count = 0;
  int wordsize = 0;

  char curr = getchar();
  checkerrorinput();

  while (curr!=EOF){
    char* word = (char*)malloc(sizeof(char));
    wordsize=0;
    while (curr!=' ' && curr!=EOF){      
      word[wordsize]=curr;
      char* tempword = (char*)realloc(word, sizeof(char) * (wordsize+2));
      if (tempword == NULL){
	free(word);
	fprintf(stderr, "Memory allocation error");
	exit(1);
      }
      wordsize++;
      word = tempword;
      curr=getchar();
    }

    word[wordsize]=' ';
    lines[count]=word;
    char** templines = (char**)realloc(lines, sizeof(char*) * (count+2));
    if (templines ==NULL){
      free(lines);
      fprintf(stderr, "Memory allocation error");
      exit(1);
    }
    count++;
    lines = templines;    
    curr = getchar();
  }

  qsort(lines, count, sizeof(char*), cmp);
  
  size_t i;
  size_t j;

  for (i=0; i<count; i++){
    for(j=0;;j++){
      putchar(lines[i][j]);
      checkerrorout();
      if(lines[i][j]==' '){
	break;
      }
    }
  }
  
  size_t c;
  for (c=0; c<count; c++){
    free(lines[c]);
  }
  free(lines);
  return 0;
}
