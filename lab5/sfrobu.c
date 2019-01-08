#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

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

int frobcmpupper(char const *a, char const *b)
{
  int aindex = 0;
  int bindex = 0;
  while(a[aindex] != ' ' && b[bindex] != ' '){
    if(toupper(a[aindex]^0x2A) > toupper(b[bindex]^0x2A))
      return 1;
    else if(toupper(b[bindex]^0x2A) > toupper(a[aindex]^0x2A))
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

int uppercmp(const void *a, const void *b){
  return frobcmpupper(*(const char**) a, *(const char**) b);
}

void checkerrorinput(int read1)
{
  if (read1<0){
    fprintf(stderr, "input error");
    exit(1);
  }
}

void checkerrorout(int write1)
{
  if (write1<0){
    fprintf(stderr, "output error");
    exit(1);
  }
}

int main(int argc, char** argv)
{
 
  int flag = 0;

  if (argc==2){
  if (strcmp(argv[1], "-f") ==0){
   flag=1;
  }
  }
 
  if(argc>2){
    fprintf(stderr, "incorrect number of args");
    exit(1);
  } else if (argc==2 && !flag){
    fprintf(stderr, "only -f option is allowed");
    exit(1);
  }
  
  char** lines = (char**)malloc(sizeof(char*));
  int count = 0;
  int wordsize = 0;
  int wordcount = 0;
  int read1;
  char curr;
  
  struct stat file1;
  if(fstat(0,&file1)<0){
    fprintf(stderr, "unable to read file");
    exit(1);
  }

  int wordcounter = 0;
  // for regular file
  if (S_ISREG(file1.st_mode)){
    char* filearr = (char*)malloc(sizeof(char)*(file1.st_size));
    read1 = read(0, filearr, file1.st_size);
    curr =filearr[0];
    int size = 0;
    int i;
    if (read1>0){
      for (i=0; i<file1.st_size; i++) {
	if (filearr[i] == ' ' || i==(file1.st_size-1)){
	  wordcounter++;
      	  while(filearr[i+1]==' '){
	   i++;
      	  }
	}
      }
    }
    
    lines = (char**)malloc(sizeof(char*)*wordcounter+1);
    
    while (count<file1.st_size) {
      char* word = (char*)malloc(sizeof(char));
      wordsize=0;
      while (curr!=' ' && count<file1.st_size){
	word[wordsize]=curr;
	char* tempword = (char*)realloc(word, sizeof(char) * (wordsize+2));
	if (tempword == NULL){
	  free(word);
	  fprintf(stderr, "Memory allocation error");
	  exit(1);
	}
	wordsize++;
	word = tempword;
	count++;
	curr = filearr[count];
      }
      if (count==file1.st_size){
	word[wordsize]=' ';
	lines[wordcount]=word;
	wordcount++;
      }else{
      word[wordsize]=' ';
      count++;
      lines[wordcount]=word;
      count++;
      curr = filearr[count];
     
      wordcount++;
      }
    }
    
  }
  
  read1 = read(0, &curr, 1);
  
  // for changing size file

  while (read1>0){
    char* word = (char*)malloc(sizeof(char));
    wordsize=0;
    while (curr!=' ' && read1>0){      
      word[wordsize]=curr;
      char* tempword = (char*)realloc(word, sizeof(char) * (wordsize+2));
      if (tempword == NULL){
	free(word);
	fprintf(stderr, "Memory allocation error");
	exit(1);
      }
      wordsize++;
      word = tempword;
      read1= read(0, &curr, 1);
    }
    
    word[wordsize]=' ';
    lines[wordcount]=word;
    char** templines = (char**)realloc(lines, sizeof(char*) * (wordcount+2));
    if (templines ==NULL){
      free(lines);
      fprintf(stderr, "Memory allocation error");
      exit(1);
    }
    wordcount++;
    lines = templines;    
    read1=read(0,&curr,1);
   
    }
  
   if (!flag){
    qsort(lines, wordcount, sizeof(char*), cmp);
   }
   else{
    qsort(lines, wordcount, sizeof(char*), uppercmp);
   }
         
  size_t r;
  size_t j;
  int write1;
  for (r=0; r<(wordcount); r++){
   for(j=0;;j++){
      write1 = write(1,&lines[r][j],1);
      //checkerrorout(write1);
      if(lines[r][j]==' '){
	break;
      }
    }
  }
   
  size_t c;
  for (c=0; c<wordcount; c++){
    free(lines[c]);
  }
  free(lines);
  //  free(filearr);
  //  free(file1);
  
return (0);

} 

