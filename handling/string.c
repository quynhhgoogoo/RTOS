#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "string.h"

int ostrlen (char*);
void ostrcpy(char *, char *);
int ostrcmp (char *, char *);
void str2upper(char *);
void str2lower(char *);
char *strdupl(char *);

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
ostrcpy(test_string,"");
str2lower(test_string);
assert(ostrcmp(test_string,"")==0);

ostrcpy(test_string,"TEST");
str2lower(test_string);
assert(ostrcmp(test_string,"test")==0);

ostrcpy(test_string,"tEsT");
str2lower(test_string);
assert(ostrcmp(test_string,"test")==0);

ostrcpy(test_string,"-TesT..-");
str2lower(test_string);
assert(ostrcmp(test_string,"-test..-")==0);
fprintf(stderr,"Ok\n");

/*************************/
fprintf(stderr,"strdupl: ");
ostrcpy(test_string,"abcdefg");
d=strdupl(test_string);
assert(ostrcmp(test_string,d)==0);
ostrcpy(test_string,"");
d=strdupl(test_string);
assert(ostrcmp(test_string,d)==0);

fprintf(stderr,"Ok\n");

/*************************/
fprintf(stderr,"\n All functions work perfectly\n");

return 0;
}
