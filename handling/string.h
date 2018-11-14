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

//creates duplicate of a string s and returns a pointer to newly created string
char *strdupl(char *s){
  char *d;
  d = (char*)malloc(50);
  ostrcpy(d,s);
  return d;
}

