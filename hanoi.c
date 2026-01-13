#include<stdio.h>
#include<math.h>
#define MAX 10

int A[MAX],B[MAX],C[MAX];
int countA=0,countB=0,countC=0;


void printrod(int n){
  printf("\n");
  for(int i=n-1;i>=0;i--){
    //rodA
    if(i<countA){
        printf(" %d",A[i]);
    }
    else{
        printf(" |");
    }
     //rodB
    if(i<countB){
        printf(" %d",B[i]);
    }
    else{
        printf(" |");
    }
     //rodC
    if(i<countC){
        printf(" %d",C[i]);
    }
    else{
        printf(" |");
    }
   printf("\n");
  }
printf("--- --- ---\n");
printf(" A   B   C \n");
 
}

void movedisk(int from[],int *countfrom,int to[],int *countto,char f,char t){

int diskfrom=(*countfrom >0)? from[*countfrom-1]:0;

int diskto=(*countto >0)? to[*countto-1]:0;

if(diskfrom==0){
    (*countto)--;
    from[*countfrom]=diskto;
    (*countfrom)++;
    printf("move disk %d from %c to %c\n",diskto,t,f);
}
else if(diskto==0){
    (*countfrom)--;
    to[*countto]=diskfrom;
    (*countto)++;
    printf("move disk %d from %c to %c\n",diskfrom,f,t);
}
else if(diskfrom >diskto){
    (*countto)--;
    from[*countfrom]=diskto;
    (*countfrom)++;
    printf("move disk %d from %c to %c\n",diskto,t,f);
}

else{
    (*countfrom)--;
    to[*countto]=diskfrom;
    (*countto)++;
    printf("move disk %d from %c to %c\n",diskfrom,f,t);
}

}

int main(){
int n=5;

int totmov=pow(2,n)-1;

for(int i=n;i>=1;i--){
    A[countA++]=i;
}

char p='A',q='B',r='C';

if(n%2==0){
    char temp=r;
    r=p;
    p=temp;
}

printf("initial\n");
printrod(n);


for(int i=1;i<=totmov;i++){
    if(i%3==1){
        movedisk(A,&countA,C,&countC,p,r);
    }
    else if(i%3==2){
        movedisk(A,&countA,B,&countB,p,q);
    }
    else{
        movedisk(B,&countB,C,&countC,q,r);
    }

    printrod(n);
}

return 0;
}