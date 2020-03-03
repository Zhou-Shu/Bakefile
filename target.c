/* CITS2002 Project 2018
   Name(s):             Zhou Shu
   Student number(s):   22552162
 */

#include"bake.h"
void target(char buff[][max_rang],int rang[],int dep,tar*h,char *arg1)
{
	//delete white space
	for(int i=0;i<dep;i++)
        {
                for(int j=0;;j++)
                {
                 if(buff[i][j]==':'||buff[i][j]=='\t')
                        {
                                while(buff[i][j-1]==' '){ space(buff,i,j-1,rang); j=j-1;}
                                while(buff[i][j+1]==' ') space(buff,i,j+1,rang);

                        }
                 if(buff[i][j]=='\0') break;
                }

        }
        // get amounts of targets and dependency
	int a[dep],b[100];
	int n=0;
	tar *p, *temp;
	temp=h;
	struct dependency *l,*r;
	int u=0;
	for(int i=0;i<dep;i++)
	{
		for(int j=0;;j++)
		{
			if(buff[i][j]=='='||buff[i][j]=='\0'||buff[i][j]=='\t') break;
			else if(buff[i][j]==':')
			{
				a[n]=i;
				b[n]=j;
				n++;
				break;
			}
		}
	}

	n=n-1;
	//test line: for(int i=0;i<=n;i++) printf("\n%d\n",a[i]);
	//establish target linked list
	for (int i=0;i<=n;i++)
	{
		p=(tar*)malloc(sizeof(tar));
		p->line=a[i];
		p->type=1;
		for(int j=0;;j++)
		{
			p->target[j]=buff[a[i]][j];
			if(buff[a[i]][j]==':')
			{
				p->target[j]='\0';
				break;
			}
		}
		l=(struct dependency *)malloc(sizeof(struct dependency));
		p->head=l;
		p->head->next=NULL;
		p->next=NULL;
		temp->next=p;
		temp=p;

	}
	p=h->next;
	/*for(int i=0;i<=n;i++)
	{
		puts(p->target);
		p=p->next;
		if(p==NULL) break;
	}*/
       
	// establish dependency linked list
	p=h->next;
	int flag=0;
	int flag1=0;
	int J;
	for(int i=0;i<=n;i++)
	{
		for(int j=0;;j++)
		{
			J=j;
			l=(struct dependency *)malloc(sizeof(struct dependency));
			for(int k=0;;k++)
			{
				if(buff[a[i]][b[i]+u+k+1]==' '){flag++;continue;}
				if(buff[a[i]][b[i]+u+k+1]=='\n'){flag1++;J=J-1; free(l); break;}
				l->dependency[k-flag]=buff[a[i]][b[i]+u+k+1];
				if(buff[a[i]][b[i]+u+k+2]==' '||buff[a[i]][b[i]+u+k+2]=='\0'||buff[a[i]][b[i]+u+k+2]=='\n'||buff[a[i]][b[i]+u+k+1]=='\0')
					{
						l->dependency[k+1]= '\0';
						l->next=p->head->next;
                                                p->head->next=l;
						u=u+k+2;
						flag=0;
						break;
					}
			}
			if(flag1){flag=0;flag1=0;break;}
			//puts(l->dependency);
			l->stackline=NULL;
			if(buff[a[i]][b[i]+u]=='\0'||buff[a[i]][b[i]+u]=='\n') break;
		}
		b[i]=J;
		//printf("\n%d\n",b[i]);
		p=p->next;
		u=0;
	}
	p=h->next;
	temp=h->next;

	// give deep targets' address to dependency which has dependency relationship with these targets
	 for(int i=0;i<=n;i++)
        {
                l=p->head->next;
                for(int j=0;j<=b[i];j++)
                {
			temp=h->next;
			for(int k=0;k<=n;k++)
			{
				if(strncmp(l->dependency,temp->target,strlen(l->dependency))==0)
				{
					l->stackline=temp;
				}
				temp=temp->next;
			}

                        l=l->next;
                }
                p=p->next;
        }

	// targets who have no dependencys will be  execute in the last
	p=h->next;
        for(int i=0;i<=n;i++)
        {
                l=p->head->next;
		if(l==NULL) p->type=2;
                /*for(int j=0;;j++)
                {
                        puts(l->dependency);
			if(l->next==NULL) break;
                        l=l->next;
                }
                printf("\n");*/
                p=p->next;
        }

	// get time of every targets and dependency 
	p=h->next;
	//long int time1;
	flag=0;
	for(int i=0;i<=n;i++)
	{
		l=p->head->next;
		if(access(p->target,0)==-1||b[i]==-1){p->time=0;}
		else
	        {
			fp=fopen(p->target,"r");
			p->time=gettime();
			fclose(fp);
		}
		for(int j=0;j<=b[i];j++)
		{
				if(access(l->dependency,0)==-1&&l->stackline==NULL)
				{
					printf("dependency %s do not exist",l->dependency);
					break;
				}
				else if(l->stackline!=NULL)
				{
					l->time=0;
				}
				else
				{
					fp=fopen(l->dependency,"r");
					l->time=gettime();
					fclose(fp);
				}
				//printf("dp: %ld \n",l->time);
				l=l->next;
		}
		//printf("tr: %ld ",p->time);
		p=p->next;
	}

	//execute most action lines
	p=h->next;
	execute(p,dep,buff,arg1);


	//execute type 2 targets
	p=h->next;
	char f=' ';
	for(int i=0;i<=n;i++)
	{
		if(p->type==2)
		{
			int a1=p->line;
			int b1;
                        if(p->next!=NULL)  b1=p->next->line;
                        else  b1=dep;
			for(int j=a1+1;j<b1;j++)
                        {
				if(buff[j][0]=='\t')
                                {
					if(buff[j][1]!='@'&&strcmp(arg1,"-s")) puts(buff[j]);
                                        else if(buff[j][1]=='@'||buff[j][1]=='-') {f=buff[j][1];buff[j][1]=' ';}
                                        if(strcmp(arg1,"-n"))
					{
                                                if(my_sys(buff[j])==EXIT_FAILURE && f!='-' && strcmp(arg1,"-i"))
                                                { printf("Action line error");exit(EXIT_FAILURE);}
                                        }
                                }
                        }
		}
		p=p->next;
	}

}
void execute (tar*p,int dep,char buff[][max_rang],char* arg1)
{
	// a recursive function to traverse the whole graph 
	struct dependency *l;
	int flag=0;
	int a,b,k=0;
	char *t,f=' ';
	if(p!=NULL)
	{
		//printf("1");
		if(p->type!=0&&p->type!=2)
		{
			//printf("2");
			l=p->head->next;
		        for(int i=0;;i++)
		        {
				if(l->stackline!=NULL) execute(l->stackline, dep,buff,arg1);
				if((fp=fopen(l->dependency,"r"))!=NULL){ l->time=gettime();}
				else printf("%s do not exist",l->dependency);
		                if(l->time>p->time) flag=1;
				if(l->next==NULL) break;
				l=l->next;
			}
			//printf("3");
			a=p->line;
			if(p->next!=NULL) b=p->next->line;
			else b=dep;
			if(flag==1)
			{
				//printf("4");
				for(int j=a+1;j<b;j++)
				{
					if(buff[j][0]=='\t')
					{
						//printf("5");
						if(buff[j][1]!='@'&&strcmp(arg1,"-s")) puts(buff[j]);
						else if(buff[j][1]=='@'||buff[j][1]=='-') {f=buff[j][1];buff[j][1]=' ';}
						if(strcmp(arg1,"-n"))
						{
							if(my_sys(buff[j])==EXIT_FAILURE && f!='-' && strcmp(arg1,"-i"))
							{ printf("Action line error");exit(EXIT_FAILURE);}
						}
					}
				}
			}
			p->type=0;
		}
		p=p->next;
		execute(p,dep,buff,arg1);
	}
}
//get time
long gettime()
{
        int fd;
        struct stat buf;
        if(NULL != fp)
    {
        fd=fileno(fp);
        fstat(fd, &buf);
        long modify_time=buf.st_mtime;
        fclose(fp);
        return modify_time;
    }
    printf("function error\n");
    return 0;
}
//a function like system 
int my_sys(char * command_line)
{
        switch(fork())
        {
                case -1: printf("fork failed"); exit(EXIT_FAILURE);
                         break;
                case 0:  execl("/bin/bash","bash","-c",command_line,NULL);
                         printf("execute error");
                         exit(EXIT_FAILURE);
                         break;
                default:{int status;
                        wait(&status);
                        return(status);}
        }
}

