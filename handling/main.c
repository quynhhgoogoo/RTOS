#include <stdio.h>
#include <assert.h>

int ostrlen (char*);
void ostrcpy(char *, char *);
int ostrcmp (char *, char *);
void str2upper(char *);
void str2lower(char *);

int main(void)
{
char test_string[100];
char *d;

/*************************/
fprintf(stderr,"Strlen: ");
assert(ostrlen("abcdefghij.-!1234124")==20);
assert(ostrlen("abc")==3);

assert(ostrlen("")==0);
assert(ostrlen("a")==1);
fprintf(stderr,"Ok\n");

/*************************/
fprintf(stderr,"Strcmp: ");
assert(ostrcmp("hei","hei")==0);
assert(ostrcmp("a","a")==0);
assert(ostrcmp("a","b")==-1);
assert(ostrcmp("b","a")==1);
assert(ostrcmp("","")==0);
assert(ostrcmp("abcdd","abcd")==1);
assert(ostrcmp("abcdsadf","abcddasdf")==1);
assert(ostrcmp("abcde","abcdf")==-1);
assert(ostrcmp("abcdeasdf","abcdfasdf")==-1);
assert(ostrcmp("abcd","abc")==1);
assert(ostrcmp("aaa","aaab")==-1);
assert(ostrcmp("abcd","abcdd")==-1);
fprintf(stderr,"Ok\n");

/*************************/
fprintf(stderr,"Strcpy: ");
ostrcpy(test_string,"Hello");
assert(ostrcmp(test_string,"Hello")==0);
ostrcpy(test_string,"");
assert(ostrcmp(test_string,"")==0);

ostrcpy(test_string,"H");
assert(ostrcmp(test_string,"H")==0);

fprintf(stderr,"Ok\n");

/*************************/
fprintf(stderr,"Str2upper & str2lower: ");

ostrcpy(test_string,"");
str2upper(test_string);
assert(ostrcmp(test_string,"")==0);

ostrcpy(test_string,"t");
str2upper(test_string);
assert(ostrcmp(test_string,"T")==0);

ostrcpy(test_string,"test");
str2upper(test_string);
assert(ostrcmp(test_string,"TEST")==0);

ostrcpy(test_string,"lEtS tRY");
str2upper(test_string);
assert(ostrcmp(test_string,"LETS TRY")==0);

ostrcpy(test_string,"te123..-_d,D--a");
str2upper(test_string);
assert(ostrcmp(test_string,"TE123..-_D,D--A")==0);

/*************************/
fprintf(stderr,"\n All functions work perfectly\n");

return 0;
}

// receive a string as a parameter and returns the length of that string
int ostrlen(char *c){

    int len;
    for (len = 0;;len++){
      if(*(c+len)=='\0'){
        break;
      }
    }
return len;
}

//copy content of string s to string d
void ostrcpy(char *d, char *s){
  int i;
  for(i=0;s[i]!=0;i++){
    *(d+i) = *(s+i);
  }
  *(d+i)='\0';
}

//compare two strings together
/*-1 if s is ordered before in alphabet that d
0 if functions are equal
+1 if d is ordered before s*/
int ostrcmp (char *s, char *d){
  int i;
  
  for(i=0;; i++){
    if(*(s+i)=='\0' && *(d+i)!='\0'){
      return -1;
    }
    if(*(d+i)=='\0' && *(s+i)!='\0'){
      return 1;
    }
    else if(*(d+i)>*(s+i)){
      return -1;
    }
    else if(*(d+i)<*(s+i)){
      return 1;
    } 
    else if (*(d+i)=='\0' && *(s+i)=='\0'){
      break;
    }   
  }
return 0;
}

//convert all small characters to upper characters
void str2upper(char *s){
  int i = 0;
   
   while (*(s+i) != '\0') {
      if (*(s+i) >= 'a' && *(s+i) <= 'z') {
         *(s+i) = *(s+i) - 32;
      }
      i++;
   }
}
void str2lower(char *s){
  int i = 0;

  while (*(s+i) != '\0') {
      if (*(s+i) >= 'A' && *(s+i) <= 'Z') {
         *(s+i) = *(s+i) + 32;
      }
      i++;
   }
}
