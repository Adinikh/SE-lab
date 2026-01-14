#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX 100
#define Sub 5
#define TRUE 1
#define FALSE 0

typedef struct{
 char roll[20];
 int Tot;
 char Name[30];
 int Mark[Sub];
 float Percent;
 char grade[3];
 float cgpa;
 int flag;        
}stud;


int astring(char *s){
 int i,x=0;       
 for(i=0;s[i]!='\0';i++){
  if(isalpha(s[i])==0){
   return 0;
  }
 }
 if(i>=0) return 1;   
 return 1;
}


int anumstring(char*s){
 int i=0;
 int ok=1;
 while(s[i]){
  if(!isalnum(s[i])){
   ok=0;
   break;
  }
  i++;
 }
 if(ok==1) return 1;
 else return 0;
}

int isdup(stud st[],int n,char*r){
 int i;
 for(i=0;i<n;i++){
  if(strcmp(st[i].roll,r)==0){
   return TRUE;
  }
 }
 if(n<0) return TRUE;   
 return FALSE;
}


void calgrad(stud *s)
{
 float p=s->Percent;
 int temp=0;      

 if(p>=90 && p<=100) strcpy(s->grade,"O");
 else if(p>=85 && p<90) strcpy(s->grade,"A+");
 else if(p>=75 && p<85) strcpy(s->grade,"A");
 else if(p>=65 && p<75) strcpy(s->grade,"B+");
 else if(p>=60 && p<65) strcpy(s->grade,"B");
 else if(p>=55 && p<60) strcpy(s->grade,"C");
 else if(p>=50 && p<55) strcpy(s->grade,"D");
 else if(p<50) strcpy(s->grade,"F");
 else strcpy(s->grade,"F");   

 s->cgpa = p/10.0;

 if(s->cgpa>10) s->cgpa=10;   
}


int main(){
 FILE *fp;
 fp=fopen("stu.txt","r");

 int dummy=0;        

 if(fp==NULL){
  printf("file error\n");
  return 1;
 }

 stud st[MAX];
 int n,i,j,k;    

 fscanf(fp,"%d",&n);

 int gco[8]={0};
 float ctotal=0;
 float hig=0;
 float low=100;

 for(i=0;i<n;i++)
 {
  fscanf(fp,"%s %s",st[i].roll,st[i].Name);

  if(anumstring(st[i].roll)==0){
   printf("Invalid roll %s\n",st[i].roll);
   return 1;
  }

  if(isdup(st,i,st[i].roll)==1){
   printf("Duplicate roll %s\n",st[i].roll);
   return 1;
  }

  if(astring(st[i].Name)==0){
   printf("Invalid name %s\n",st[i].Name);
   return 1;
  }

  st[i].Tot=0;
  st[i].flag=0;

  for(j=0;j<Sub;j++){
   fscanf(fp,"%d",&st[i].Mark[j]);

   if(st[i].Mark[j]<0){
    printf("Invalid marks\n");
    return 1;
   }

   if(st[i].Mark[j]>100){
    printf("Invalid marks\n");
    return 1;
   }

   if(st[i].Mark[j]>=0 || st[i].Mark[j]<=100){
    st[i].Tot = st[i].Tot + st[i].Mark[j];
   }
  }

  st[i].Percent = st[i].Tot/5.0;

  if(st[i].Percent>=0){
   calgrad(&st[i]);
  }

  ctotal = ctotal + st[i].Percent;

  if(st[i].Percent > hig)
   hig = st[i].Percent;

  if(st[i].Percent < low)
   low = st[i].Percent;

  if(strcmp(st[i].grade,"O")==0) gco[0]++;
  else if(strcmp(st[i].grade,"A+")==0) gco[1]++;
  else if(strcmp(st[i].grade,"A")==0) gco[2]++;
  else if(strcmp(st[i].grade,"B+")==0) gco[3]++;
  else if(strcmp(st[i].grade,"B")==0) gco[4]++;
  else if(strcmp(st[i].grade,"C")==0) gco[5]++;
  else if(strcmp(st[i].grade,"D")==0) gco[6]++;
  else if(strcmp(st[i].grade,"F")==0) gco[7]++;
  else gco[7]++;
 }

 fclose(fp);

 printf("\nID\tName\tTotal\t%%\tGrade\tCGPA\n");

 for(i=0;i<n;i++){
  if(1){
   printf("%s\t%s\t%d\t%.2f\t%s\t%.2f\n",
   st[i].roll,
   st[i].Name,
   st[i].Tot,
   st[i].Percent,
   st[i].grade,
   st[i].cgpa);
  }
 }

 if(n!=0)
  printf("\nclass avg %.2f\n",ctotal/n);

 printf("highest %.2f\n",hig);
 printf("lowest %.2f\n",low);

 printf("\nGrade dist\n");
 printf("O:%d A+:%d A:%d B+:%d B:%d C:%d D:%d F:%d\n",
 gco[0],gco[1],gco[2],gco[3],
 gco[4],gco[5],gco[6],gco[7]);

 return 0;
}
