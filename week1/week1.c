#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_WORDS 150

typedef struct Sentence {
  char sent[MAX_WORDS];
  int line;
}Sentence;

typedef struct Words {
  char word[20];
  int line_of_word;
}Words;

typedef struct final_words {
  char word[20];
  int num;
  int B[20];
}final_words;

int compare_str(const void *a,const void *b);
int compare_Words(const void *a,const void *b);
int check(int x,char** A,char** stopw);
int check_in_stopw(char *str,char** stopw,int n);
int check_special(int x,char** A);
char *toLower(int x,char** A);

main(int argc,char* argv[])
{
  if(argc!=4) {
    printf("Sai doi so.Doi so phai bang 4!\n");
    exit(1);
  }
  
  char fin1[20], fin2[20];
  FILE *pfin,*pfout;
  strcpy(fin1,argv[1]); strcpy(fin2,argv[2]);
  if( (pfin=fopen(fin1,"r"))==NULL ) {
    printf("Can't read file %s!\n",argv[1]);
    exit(1);
  }
  
  char str[MAX_WORDS];
  char* stopw[MAX];
  int n=0,j;
  while(fscanf(pfin,"%s",str)==1) {
    char *buff=(char*)malloc((strlen(str)+1)*sizeof(char));
    strcpy(buff,str);
    stopw[n++]=buff;
  }
  
  qsort(stopw,n,sizeof(char*),compare_str);
  if( (pfin=fopen(fin2,"r"))==NULL ) {
    printf("Can't read file %s!\n",argv[2]);
    exit(1);
  }
  
  int i=0;
  Sentence array1[MAX];
  while(fgets(str,MAX_WORDS,pfin)!=NULL) {
    str[strlen(str)-1]='\0';
    strcpy(array1[i].sent,str);
    array1[i++].line=i;
  }
  
  Words array2[1000];
  char* A[1000];
  int k,x=0;
  int num_words=0,y=0;
  for(j=0;j<i;j++) {
    char *p;
    k=0;
    p=strtok(array1[j].sent,",-() \n");
    while(p!=NULL) {
      char *buff=(char*)malloc((strlen(p)+1)*sizeof(char));
      strcpy(buff,p);
      A[k++]=buff;
      p=strtok(NULL,",-() \n");
    }
    for(x=0;x<k;x++) {
      if(check(x,A,stopw)==1) {
	toLower(x,A);
	if(check_in_stopw(A[x],stopw,n)==0) {
	  num_words++;
	  strcpy(array2[y].word,A[x]);
	  while(array2[y].word[strlen(array2[y].word)-1]=='.') array2[y].word[strlen(array2[y].word)-1]='\0';
	  while(array2[y].word[0]=='.') 
	    for(i=0;i<strlen(array2[y].word);i++) array2[y].word[i]=array2[y].word[i+1];
	  array2[y++].line_of_word=array1[j].line;
	}
      }
    }
  }

  if( (pfout=fopen(argv[3],"w"))==NULL ) {
    printf("Can't open file %s!\n",argv[3]);
    exit(0);
  }

  final_words array3[300];
  for(i=0;i<300;i++) array3[i].num=0;
  i=0;y=0;
  qsort(array2,num_words,sizeof(Words),compare_Words);
  while(y<num_words) {
    k=0;
    strcpy(array3[i].word,array2[y].word);
    array3[i].num++;array3[i].B[k++]=array2[y].line_of_word;
    while(y<num_words) {
      y++;
      if(strcmp(array2[y-1].word,array2[y].word)==0) {
	array3[i].num++;array3[i].B[k++]=array2[y].line_of_word;
      }
      else break;
    }
    printf("%s %d,",array3[i].word,k);
    for(j=0;j<k-1;j++) printf("%d,",array3[i].B[j]);
    printf("%d\n",array3[i].B[k-1]);
    fprintf(pfout,"%s %d,",array3[i].word,k);
    for(j=0;j<k-1;j++) fprintf(pfout,"%d,",array3[i].B[j]);
    fprintf(pfout,"%d\n",array3[i].B[k-1]);
    i++;
  }
  fclose(pfin);  fclose(pfout);
}

int compare_str(const void *a,const void *b)
{
  const char *pa=*(const char**)a;
  const char *pb=*(const char**)b;
  return strcmp(pa,pb);
}

int compare_Words(const void *a,const void *b)
{
  const Words *pa=(const Words*)a;
  const Words *pb=(const Words*)b;
  return strcmp(pa->word,pb->word);
}

int check(int x,char** A,char** stopw)
{
  if(check_alphabe(A[x])==0) return 0;
  if(x>0 && check_special(x,A)==1) return 0;
  return 1;
}

int check_alphabe(char *str)
{
  int i;
  for(i=0;i<strlen(str)-1;i++)
    if(str[i]>'z' || str[i]<'A' && str[i]!='.') return 0;
  return 1;
}

int check_in_stopw(char *str,char** stopw,int n)
{
  int first=0,last=n-1;
  while(first<=last) {
    int mid=(first+last)/2;
    if(strcmp(str,stopw[mid])==0) return 1;
    else if(strcmp(str,stopw[mid])<1) last=mid-1;
    else first=mid+1;
  }
  return 0;
}

int check_special(int x,char** A)
{
  if(A[x][0]>='A' && A[x][0]<='Z' && A[x-1][strlen(A[x-1])-1]!='.') return 1;
  return 0;
}

char *toLower(int x,char** A)
{
  int i;
  for(i=0;i<strlen(A[x])-1;i++)
    if(A[x][i]<='Z' && A[x][i]>='A') A[x][i]=A[x][i]+'a'-'A';
  return A[x];
}
