#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
struct nc
{
int acc;
char pin[2];
int bal;
};
typedef struct nc n;
void New();
void old();
void withdraw(int x,int a);
void deposit(int x,int a);
void credit(int x,int am,int t);
int search(int o);
void main()
{
int n;
do
{
clrscr();
printf("Welcome\n1.New acc\n2.Old acc\n");
scanf("%d",&n);
switch(n)
{
case 1:New();
       break;
case 2:old();
       break;
case 3:exit(0);
}
getch();
}while(1);
}

void New()
{
FILE *fp;
n a;
fp=fopen("acc.txt","a");
printf("Enter acc no:");
scanf("%d",&a.acc);
printf("Enter pin:");
flushall();
gets(a.pin);
printf("Enter initial balance(min rs 100/-):");
scanf("%d",&a.bal);
fwrite(&a,sizeof(n),1,fp);
printf("Your details\nacc_no:%d\npin:*%c\nbal:%d",a.acc,a.pin[1],a.bal);
fclose(fp);
}

void old()
{
FILE *fp;
n a;
int x,op,flag=0,am,t;
char p[2];
fp=fopen("acc.txt","r");
printf("Enter Your acc no:");
scanf("%d",&x);
while(1)
{
	if(feof(fp))
		break;
		else
		{
		fread(&a,sizeof(n),1,fp);
			if(x==a.acc)
			{
			flag=1;
			goto m;
			}
		}
}
if(flag==0)
{	printf("acc not found");     goto n;}

m:
printf("Enter your pin:");
flushall();
scanf("%s",p);
if(p[0]==a.pin[0]&&p[1]==a.pin[1])
{
printf("enter your required option\n1.Balance enquiry\n2.Withdrawl\n3.Deposit\n4.Credit\n");
scanf("%d",&op);
switch(op)
{
case 1:printf("\nYour balance is %d",a.bal);
	fclose(fp);
       break;
case 2:printf("Enter the amount:");
	z:
	scanf("%d",&am);
		if(am%100!=0)
			{  printf("Reenterthe amount\n");
			   goto z;
			}
       withdraw(am,a.acc);
       fclose(fp);
       break;
case 3:printf("Enter the amount:");
	w:
	scanf("%d",&am);
		if(am%100!=0)
			{  printf("Reenterthe amount\n");
			   goto w;
			}
       deposit(am,a.acc);
       fclose(fp);
       break;
case 4:printf("Enter target acc:");
       scanf("%d",&t);
       printf("enter amount:");
       p:
       scanf("%d",&am);
	if(am%100!=0)
	{
	printf("renenter amount\n");
	goto p;
	}
	credit(a.acc,am,t);
	fclose(fp);
	break;

}
n:
}
}

void withdraw(int x,int q)
{
FILE *fp,*fp1;
n a,b;
int i;
fp=fopen("acc.txt","r");
if(fp==NULL)
{      printf("File not found");
	goto t;
}
fp1=fopen("temp.txt","w");
while(1)
{
f:
fread(&a,sizeof(n),1,fp);
if(feof(fp))
	break;
if(q==a.acc)
{
b.acc=a.acc;
for(i=0;i<2;i++)
    b.pin[i]=a.pin[i];
b.bal=a.bal-x;
fwrite(&b,sizeof(n),1,fp1);
goto f;
}
if(a.acc!=q)
fwrite(&a,sizeof(n),1,fp1);
}
printf("your reamining bal=%d",b.bal);
fclose(fp);
fclose(fp1);
remove("acc.txt");
rename("temp.txt","acc.txt");
t:
}

void deposit(int x,int q)
{
FILE *fp,*fp1;
n a,b;
int i;
fp=fopen("acc.txt","r");
if(fp==NULL)
{      printf("File not found");
	goto t;
}
fp1=fopen("temp.txt","w");
while(1)
{
f:
fread(&a,sizeof(n),1,fp);
if(feof(fp))
	break;
if(q==a.acc)
{
b.acc=a.acc;
for(i=0;i<2;i++)
    b.pin[i]=a.pin[i];
b.bal=a.bal+x;
fwrite(&b,sizeof(n),1,fp1);
goto f;
}
if(a.acc!=q)
fwrite(&a,sizeof(n),1,fp1);
}
printf("your reamining bal=%d",b.bal);
fclose(fp);
fclose(fp1);
remove("acc.txt");
rename("temp.txt","acc.txt");
t:
}

void credit(int x,int am,int t)
{
FILE *fp,*fp1;
int i,k;
n a,b,c;
fp=fopen("acc.txt","r");
fp1=fopen("temp.txt","w");
if(fp==NULL)
{
printf("NO data found");
goto b;
}
k=search(t);

if(k==0)
{  printf("target acc not found\n");
	goto b;
}
else
{
while(1)
{
h:
fread(&a,sizeof(n),1,fp);
if(feof(fp))
	break;
if(x==a.acc)
{
b.acc=a.acc;
for(i=0;i<2;i++)
	b.pin[i]=a.pin[i];
b.bal=a.bal-am;
fwrite(&b,sizeof(n),1,fp1);
goto h;
}
else if(t==a.acc)
{
c.acc=a.acc;
for(i=0;i<2;i++)
	c.pin[i]=a.pin[i];
c.bal=a.bal+am;
fwrite(&c,sizeof(n),1,fp1);
goto h;
}
else
fwrite(&a,sizeof(n),1,fp1);
}
}

fclose(fp);
fclose(fp1);
remove("acc.txt");
rename("temp.txt","acc.txt");
b:
}

int search(int o)
{
FILE *fp;
int flag=0;
n a;
fp=fopen("acc.txt","r");
while(1)
{
fread(&a,sizeof(n),1,fp);
if(feof(fp))
break;
if(o==a.acc)
{
flag=1;
}
}
fclose(fp);
if(flag==1)
	return 1;
else
	return 0;
}







