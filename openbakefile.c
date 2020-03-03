/* CITS2002 Project 2018
   Name(s):             Zhou Shu
   Student number(s):   22552162
 */

# include "bake.h"
// open bakefile
void openbakefile(char*bakefile_name,char*arg1)
{
	if(strcmp(arg1,"-f"))
	{
	int a,b;
	a=access("bakefile",R_OK);
	b=access("Bakefile",R_OK);
	if(a==-1&&b==-1)
	{
		printf("bakefile don't exit\n");
		exit(EXIT_FAILURE);
	}
	else if(a>b)
	{
		fp=fopen("bakefile","r");
		if(fp==NULL) 
		{
			printf("open file error\n");
			exit(0);
		}
		//else printf("open successfully1\n");
	
	}
	else if(a<b||(a==0&&b==0))
	{
		fp=fopen("Bakefile","r");
		if(fp==NULL)
                {
                        printf("open file error\n");
                        exit(EXIT_FAILURE);
                }

		//else printf("open successfully2\n");
        }
	}
	else
	{
		if((fp=fopen(bakefile_name,"r"))==NULL) { printf("open bakefile error\n");exit(EXIT_FAILURE);}
		//else printf("open successfully3\n");
	}
}

// get depth of bakefile
int depth(void)
{
        char a[100];
        int n=0;
        while(fgets(a,100,fp)!=NULL)
        {
                n++;

        }
        return n;

}

// get bakefile
void get_bakefile(char buff[][max_rang],int rang[],int*dep)
{
        int i=0;
        while((fgets(buff[i++],max_rang,fp))!=NULL)
        {
                for(int n=0;;n++)
                {
                        if(buff[i-1][n]=='#')
                        {
                                buff[i-1][n]='\0';
                        }
                        /*if(buff[i-1][n]==' ')
                        {

                                for(int r=n;;r++)
                                {
                                        buff[i-1][r]=buff[i-1][r+1];
                                        if(buff[i-1][r]=='\0')
                                        {
                                                break;
                                        }

                                }
                                n-1;
                        }*/

                        if(buff[i-1][n]=='\0')
                        {
                                rang[i-1]=n+1;
                                 if(buff[i-1][n-2]=='\\')
                                {
                                        fgets(buff[i-1]+n-2,max_rang-rang[i-1]+2,fp);
                                        continue;
                                }

                                break;
                        }

                }
                *dep=i;

        }

}

//print bakefile
void print_bakefile(char buff[][max_rang],int rang[],int dep)
{
        int flag=0;
        //printf("\nthe amount of lines is %d\n",dep);
        printf("content of bakefile:\n");
        for(int k=0;k<dep;k++)
        {
                if(buff[k][0]=='\n'||buff[k][0]=='\0') continue;
                for(int i=0;;i++)
                {
                        if(buff[k][i]=='\t') break;
                        if(buff[k][i]=='=') flag=1;
                        else if (buff[k][i]=='\0') break;
                }
                if(flag) {flag=0;continue;}
                for(int j=0;;j++)
                {
                        if (buff[k][j]=='\0')
                        {
                                //printf("\\0");
                                break;
                        }
                        //if (buff[k][j]=='\n') printf("\\n");
                        //if(buff[k][j]=='\t') printf("\\t");
                        else printf("%c",buff[k][j]);
                }
                printf("\n");

        }
        printf("\n");
        exit(EXIT_SUCCESS);


        /*for(int n=0;n<dep;n++)
        {
                printf("the rang of line%d is %d\n",n+1,rang[n]);
        }*/
}

//delete white space
void space(char buff[][max_rang],int i,int j,int rang[])
{
        if(buff[i][j]==' ')
        {
		for(int r=j;;r++)
                {
			buff[i][r]=buff[i][r+1];
			if(buff[i][r]=='\0') break;
                }
        }
        rang[i]=rang[i]-1;
}

