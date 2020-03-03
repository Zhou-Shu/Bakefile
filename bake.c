/* CITS2002 Project 2018
   Name(s):             Zhou Shu
   Student number(s):   22552162
 */

#include"bake.h"
int main(int argc,char*argv[])
{
	char bakefile_name[30];
	char arg1[4];
	if(argc>1)//get parameters
	{
		strcpy(arg1,argv[1]);
		if(!strcmp("-C",argv[1]))
		{
			if(opendir(argv[2])==NULL) printf("dir don't exist");
			else chdir(argv[2]);
		}
		else if(!strcmp("-f",argv[1])) strcpy(bakefile_name,argv[2]);
		else if(strcmp("-i",argv[1])&&strcmp("-n",argv[1])&&strcmp("-p",argv[1])&&strcmp("-s",argv[1])) printf("%s is illegal",argv[1]);
	}


	openbakefile(bakefile_name,arg1);//checking if the file exists, and open bakefile
	int dep=depth();//finding the amount of lines
	
	fseek(fp,0L,SEEK_SET);

	char buff[dep][max_rang];
	int rang[dep];
	int *pdep;
	pdep=&dep;
        
	get_bakefile(buff,rang,pdep);// inputting file's date to buff,and optimizing it
	
        
	if(fp==NULL)
	{
		printf("close error");
		exit(0);
	}
        fclose(fp);

	variable(buff,rang,dep);// variable substituion

	if(argc>1){if(!strcmp("-p",argv[1])) print_bakefile(buff,rang,dep);}// printing the information of bakefile
        
	tar *h;// initialize head node of target
	h=(tar*)malloc(sizeof(tar));
	h->next=NULL;
	
	target(buff,rang,dep,h,arg1);// store targets and dependencies, then executing all of action line
	
}
