/* CITS2002 Project 2018
   Name(s):             Zhou Shu
   Student number(s):   22552162
 */

#include"bake.h"
void variable(char buff[][max_rang],int rang[],int dep)
{
	char name[dep+4][100],cwd[100];
	char value[dep+4][100];
	name[0][0]='P';
	name[0][1]='I';
	name[0][2]='D';
        name[0][3]='\0';
        name[1][0]='P';
        name[1][1]='P';
        name[1][2]='I';
        name[1][3]='D';
        name[1][4]='\0';
        name[2][0]='P';
        name[2][1]='W';
        name[2][2]='D';
        name[2][3]='\0';
        name[3][0]='R';
        name[3][1]='A';
        name[3][2]='N';
        name[3][3]='D';
	name[3][4]='\0';
	sprintf(value[0],"%d",getpid());
        sprintf(value[1],"%d",getppid());
        sprintf(value[3],"%d",rand());
        sprintf(value[2],"%s",getcwd(cwd,sizeof(cwd)));
	int n=4;
	//delete white space
	for(int i=0;i<dep-1;i++)
	{
		for(int j=0;;j++)
		{
		 if(buff[i][j]=='=')
                        {
                                while(buff[i][j-1]==' '){ space(buff,i,j-1,rang); j=j-1;}
                                while(buff[i][j+1]==' ') space(buff,i,j+1,rang);

			}
		 if(buff[i][j]=='\0') break;
		}

	}

// store name and value to array
	for(int i=0;i<dep-1;i++)
	{
		for(int j=0;;j++)
		{
			if(buff[i][j]=='\t') break;
			if(buff[i][j]=='=')
			{

				for(int k=0;k<j;k++)
				{
					name[n][k]=buff[i][k];

				}
				name[n][j]='\0';
				for(int k=0;;k++)
				{
					if((buff[i][k+j+1]=='\n')||(buff[i][k+j+1]=='\0'))
					{
						if(k==0)
						{
							if(getenv(name[n])!=NULL)
							{strcpy(value[n],getenv(name[n]));
							break;}
						}
						value[n][k]='\0';
                                                break;
					}
					else
					{
						value[n][k]=buff[i][k+j+1];

					}

				}
				n=n+1;


			}
			if(buff[i][j]=='\0') break;
		}

	}

	/*test line
        printf("\n the variable subsititution:\n");
	for(int i=0;i<n;i++)
	{
		for(int t=0;;t++)
		{
			if(name[i][t]=='\0')
			{
				printf("0 ");
				break;
			}
			printf("%c",name[i][t]);
		}
		printf("=");
		for(int t=0;;t++)
		{
		        if(value[i][t]=='\0')
			{
				printf("0 ");
				break;
			}
			printf("%c",value[i][t]);
		}
		printf("\n%d\n",n);
	}*/

	
	subsititution(name,value,n,buff,dep,rang);
}






void subsititution(char name[][100],char value[][100],int n,char buff[][max_rang],int dep,int rang[])
{
	int x=0;
	int flag=0;
	int flag1=0;
	// variable subsitution
	for(int i=0;i<dep;i++)
	{

		for(int j=0;;j++)
		{
			//printf("i=%d\n",i);
			if(buff[i][j]=='\0')
                         {
                                 //printf("1");
                                 break;
                         }
			else if((buff[i][j]=='$')&&(buff[i][j+1]=='('))
			{
				//printf("buff[%d][%d]=%c",i,j,buff[i][j]);
				for(int k=0;k<n;k++)
				{
					for(int l=0;;l++)
						{
							if((buff[i][j+2+l]==')')&&(l!=0))
							{
								x=j+2+l;
								//printf("3");
								flag=1;
								int length=0;
								while(value[k][length]!='\0') length++;
								int dif=length-l-3;
								if(dif>0)
								{
									for(int b=rang[i]-1;b>j+2+l;b--)
                                                                        {
										buff[i][b+dif]=buff[i][b];
                                                                        }

								}
								else
								{
									for(int y=0;y<=rang[i]-j-l-3;y++)
									{
										buff[i][j+3+l+y+dif]=buff[i][j+3+l+y];
									}
								}
								rang[i]=rang[i]+length-l-3;
								//printf("buff=%c\n",buff[i][rang[i]+dif]);
								for(int u=0;u<length;u++)
								{
									//printf("5");
									buff[i][j+u]=value[k][u];
								}
								j=j-1;
								break;
							}
							if(buff[i][j+2+l]!=name[k][l]) break;
						}
					if(flag==1) {flag=0; break;}
				}
	
                        }

		}
	}

	//get value of environment
	for(int i=0;i<dep;i++)
	{
		for(int j=0;;j++)
		{
			if(buff[i][j]=='$')
			{
				int stat=j;
				int end;
				for(end=j;;end++){if(buff[i][end]==')') break;}
				evn(buff[i],stat,end);
			}
			if(buff[i][j]=='\0') break;
		}
        }

}

// value subsistution of environment
int evn(char* line,int stat,int end)
{
        char line1[100];
        char line2[100];
        char line3[100];
        strncpy(line1,line+stat+2,end-stat-2);
        line1[end-stat-2]='\0';
        if(getenv(line1)==NULL) line3[0]='\0';
        else strcpy(line3,getenv(line1));
        strncpy(line2,line,stat);
        strncat(line2,line3,strlen(line3));
        strncat(line2,line+end+1,strlen(line)-end);
        strcpy(line,line2);
        return 1;

}

