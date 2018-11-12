#include <stdio.h>
#include <stdlib.h>
struct state{
int input[100];
int isFinal;
int current_set;
int last_set;
int value;
}table[100];
char input[100];
struct state optimized[100];
void compute_value(int ,int);
int generate_current_set(int );
void current_to_last(int );
void change_name(int,int,int);
void print(struct state *,int,int);
int main()
{
    int n,m,t=-1,set=2,i,j,key,q,flag,p,u;
    printf("How many states in DFA");
    scanf("%d",&n);
    printf("How many inputs in DFA");
    scanf("%d",&m);
    fflush(stdin);
    gets(input);
    for(int i=0;i<n;i++)
    {
        printf("Input state table for %d\n",i);
       for(j=0;j<m;j++)
       {
           printf("Input %c \t",input[j]);
           scanf("%d",&table[i].input[j]);
       }
       printf("Is %d a final state",i);
       scanf("%d",&table[i].last_set);
       table[i].isFinal=table[i].last_set;
    }
    flag=0;
    q=1;
    p=3;
    print(table,n-1,m);
    u=0;
while(p!=q)
{
    //compute function calculates the set value of every state and then adds all the set values in array aar1 and returns the size of array aar1
    if(flag==1)
    {
        q=p;
    }
    compute_value(n,m);
    p=generate_current_set(n);
    current_to_last(n);
    printf("\n\n\t %d equivalent \t\t",++u);
    for(int i=0;i<n;i++)
    printf("%d",table[i].current_set);
        printf("\n");
    flag=1;
}
change_name(n,p,m);
//printf("%d",p);
print(optimized,p,m);
}
void compute_value(int n,int m)
{
    int ans,c;
    for(int i=0;i<n;i++)
    {
        ans=0;
        c=1;
        for(int j=0;j<m;j++)
        {
            ans=ans+table[table[i].input[j]].last_set*c;
            c*=10;
        }
        table[i].value=ans;
    }
}
int generate_current_set(int n)
{
    int c=-1,flag;
    for(int i=0;i<n;i++)
    {
        flag=0;
        for( int j=i-1;j>=0;j--)
        {
           if(table[i].last_set==table[j].last_set&&table[i].value==table[j].value)
            {
                table[i].current_set=table[j].current_set;
                flag=1;
                break;
            }
        }
         if(flag!=1)
            {
                c++;
                table[i].current_set=c;
            }

    }
    return c;
}
void current_to_last(int n)
{
    for(int i=0;i<n;i++)
    {
        table[i].last_set=table[i].current_set;
    }
}
void change_name(int n,int c,int m)
{
  for(int i=0;i<=c;i++)
  {
    for(int j=0;j<n;j++)
    {
        if(table[j].current_set==i)
        {
            for(int k=0;k<m;k++)
            optimized[i].input[k]=table[j].input[k];
            optimized[i].isFinal=table[j].isFinal;
             break;
        }
    }

  }
  for(int i=0;i<=c;i++)
  {
      for(int j=0;j<m;j++)
      {

              optimized[i].input[j]=table[optimized[i].input[j]].current_set;
      }
  }
}
void print(struct state* tabl,int n,int m)
{
    int i,j;
    printf("\n\n\n\ns/i");
    for(j=0;j<m;j++)
    {
        printf("\t%c",input[j]);
    }
    printf("\n");
    for(i=0;i<=n;i++)
    {
        printf("%d",i);
        if(tabl[i].isFinal==1)
            printf("*\t");
        else
            printf("\t");
        for(j=0;j<m;j++)
        {
           printf("%d\t",tabl[i].input[j]);
        }
        printf("\n");
    }
}
