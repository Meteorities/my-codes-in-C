#include<stdio.h>
#include "fuck.h"

struct kongkuai  //Copy structure once again
{
int startaddr;
int size;
int flag;
};

extern struct kongkuai kongxq[6];

int allocate(int jobsize) {
int i;
int t=0;
for(i=0;i<6;i++)
if(kongxq[i].flag==1&&kongxq[i].size>jobsize)
{

kongxq[i].startaddr+=jobsize;
kongxq[i].size-=jobsize;
t=1;

return kongxq[i].startaddr-jobsize;

}
else
if(kongxq[i].flag==1&&kongxq[i].size==jobsize)

{

kongxq[i].flag=0;

t=1;

return kongxq[i].startaddr;

}

if(t==0)

return false;

return 1;

}

int circle()

{

int i,j;

struct kongkuai temp;

for(i=0;i<6;i++)

for(j=0;j<6;j++)

if(kongxq[j].size>kongxq[j+1].size)

{

temp.startaddr=kongxq[j].startaddr;

temp.size=kongxq[j].size;

temp.flag=kongxq[j].flag;

kongxq[j].startaddr=kongxq[j+1].startaddr;

kongxq[j].size=kongxq[j+1].size;

kongxq[j].flag=kongxq[j+1].flag;

kongxq[j+1].startaddr=temp.startaddr;

kongxq[j+1].size=temp.size;

kongxq[j+1].flag=temp.flag;

}

for(i=0;i<6;i++)

for(j=0;j<6;j++)

if(kongxq[j].flag==0&&kongxq[j+1].flag==1)

{

temp.startaddr=kongxq[j].startaddr;

temp.size=kongxq[j].size;

temp.flag=kongxq[j].flag;

kongxq[j].startaddr=kongxq[j+1].startaddr;

kongxq[j].size=kongxq[j+1].size;

kongxq[j].flag=kongxq[j+1].flag;

kongxq[j+1].startaddr=temp.startaddr;

kongxq[j+1].size=temp.size;

kongxq[j+1].flag=temp.flag;

}

return 1;

}

int callback()

{

int s,len,t1=0,t2=0,t3=0,i,j;
printf("请输入回收区的起始地址:\n");
scanf("%d",&s);
printf("请输入回收区的大小:\n");
scanf("%d",&len);
for(i=0;i<6;i++)
{
if((kongxq[i].startaddr==s+len)&&(kongxq[i].flag==1))

{

len+=kongxq[i].size;
t1=1;

for(j=0;j<6;j++)

if((kongxq[j].startaddr+kongxq[j].size==s)&&(kongxq[j].flag==1))

{

kongxq[i].flag=0;

//kongxq[j].startaddr=

kongxq[j].size=kongxq[j].size+len;
t2=1;

break;

}

if(t2==0)

{

kongxq[i].startaddr=s;

kongxq[i].size=len;

break;

}

}

}

if(t1==0)

{

for(i=0;i<6;i++)

{

if((kongxq[i].startaddr+kongxq[i].size==s)&&(kongxq[i].flag==1))

{

kongxq[i].size+=len;

t3=1;

break;

}

if(t3==0)

for(j=0;j<6;j++)

if(kongxq[j].flag==0)

{

kongxq[j].startaddr=s;

kongxq[j].size=len;

kongxq[j].flag=1;

break;

}

}

}

return 1;

}

void print()
{
int i;
printf("\n 起始地址 | 大小 | 标记 \n\n");

for(i=0;i<6;i++)

{
printf(" %3d | %3d | %3d \n",

kongxq[i].startaddr,kongxq[i].size,kongxq[i].flag);

}

printf("\n");

}

//void main()
int main()
{
int jobsize,start;
char end;
printf("\n是否有作业请求空闲区,y or n:");

while((end=getchar())=='y')

{

printf("初始空闲区状态:\n");

circle();

print();

printf("请输入请求空闲区的作业大小:");

scanf("%d",&jobsize);

start=allocate(jobsize);

circle();

printf("分配后空闲区状态:\n");

print();

if(!start)

printf("没有适合的空闲区大小～\n");

else

printf("作业起始地址:%d\n",start);

printf("作业大小:%d\n",jobsize);

callback();

circle();

print();

printf("是否有其他的作业请求, y or n:");

end=getchar();

}

//新增加
return 0;
}