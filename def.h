#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Partition
{
	char name[20];
	int start;
	int size;
	struct Partition* next;
}Partition;

typedef struct Process
{
	int excute_time;
	char name[20];
	int size;
	int start;	
	int status;                 //�������������״̬������������������	
	struct Process* next;
}Process;
