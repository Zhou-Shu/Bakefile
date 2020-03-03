/* CITS2002 Project 2018
   Name(s):		Zhou Shu 
   Student number(s):	22552162
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <dirent.h>
#define max_rang 200
extern void openbakefile(char*,char*); // open bakefile 
extern int depth(void);// find amounts of bakefile's row
extern void get_bakefile(char(*)[max_rang],int(*),int *); // tranfer bakefile to array 'buff'
extern void print_bakefile(char(*)[max_rang],int(*),int);// print bakefile
extern void variable(char(*)[max_rang],int(*),int);// get name and value
extern void subsititution(char(*)[100],char(*)[100],int,char(*)[max_rang],int,int(*));// variable subsititution
extern void space(char (*)[max_rang],int,int,int(*));// delete space
extern int evn(char* ,int ,int);// get value of environment

FILE *fp;
extern long gettime(void);//get modified time
struct target;
typedef struct dependency// single linked list
{
	char dependency[max_rang];
	struct dependency *next; // next node's address
	struct target *stackline;// a dependency might be generate by other target line, here is target line's address
	long int time;// dependency's modified time
}dp;

typedef struct target// single linked list
{
	struct dependency *head;// head node of dependency's linked list
	char target[max_rang];
	int line;// the place of target line in bakefile
	int type;//need to be executed is 1,do not need or have been executed is 0, no dependency is 2 
	struct target *next;// next node's address
	long int time;// target's modified time

}tar;
extern void target(char (*)[max_rang],int(*),int,tar*,char*);// split targets and dependency 
extern void execute (tar*,int,char(*)[max_rang],char*);// a recursion function which can traverse my graph and sequential execute action lines 
extern int my_sys(char *);// fork()+execul()+wait()=system()
