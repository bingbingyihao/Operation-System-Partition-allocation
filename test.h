#include "partition.h"


void Process_insert(Process* process_head, int process_num) {
	int i, _start, _size, _excute_time;
	char _name[20];
	Process* current = process_head;

	while (i < process_num) {
		Process* _new = (Process*)malloc(sizeof(Process));
		printf("进程名称：");
		scanf("%s", _name);
		printf("进程大小：");
		scanf("%d", &_size);
		printf("执行时间：");
		scanf("%d", &_excute_time);

		strcpy(_new->name, _name);
		_new->start = -1;
		_new->size = _size;
		_new->excute_time = _excute_time;
		_new->status = 1;
		_new->next = NULL;

		while (current->next != NULL)
			current = current->next;
		current->next = _new;

		i++;
	}
}

void Print_process(Process* process_head) {
	Process* current = process_head->next;
	printf("**********************************************************************************************\n");	
	printf("\t进程名称\t开始位置\t进程大小\t执行时间\t进程状态\n");
	printf("\n");
	while (current) {
		printf("\t");
		printf("%s\t\t", current->name);
		printf("%d\t\t", current->start);
		printf("%d\t\t", current->size);
		printf("%d\t\t", current->excute_time);

		switch (current->status)
		{
		case 1:
			printf("创建状态\n");
			break;
		case 2:
			printf("就绪状态\n");
			break;		
		case 3:
			printf("阻塞状态\n");
			break;		
		default:
			printf("ERROR\n");
			break;
		}

		current = current->next;
	}
	printf("**********************************************************************************************\n");
}

void Partition_insert(Partition* partition_head, int partition_num) {
	int i = 0, _start, _size;
	char _name[20];
	Partition* current = partition_head;

	while (i < partition_num) {
		Partition* _new = (Partition*)malloc(sizeof(Partition));
		printf("空闲区名称：");
		scanf("%s", _name);
		printf("开始位置：");
		scanf("%d", &_start);
		printf("区间大小：");
		scanf("%d", &_size);
		strcpy(_new->name, _name);
		_new->start = _start;
		_new->size = _size;
		_new->next = NULL;
		while (current->next != NULL)
			current = current->next;
		current->next = _new;
		i++;
		printf("\n");
	}
}

void Print_partition(Partition* partition_head) {
	Partition* current = partition_head->next;
	printf("**********************************************************************************************\n");	
	printf("\t\t\t空闲区名称\t开始位置\t区间长度\n");
	while (current) {
		printf("\t\t\t");
		if (!current->name)
			printf("\t\t  ");
		else
			printf("%s\t\t  ", current->name);		
		printf("%d\t\t", current->start);
		printf("%d\n", current->size);
		current = current->next;
	}
	printf("**********************************************************************************************\n");
}

void Print_menu() {
	printf("************************************************************************************************************************\n");
	printf("\t\t1、插入空闲区\t2、分配空闲区\t3、查看空闲区\t4、回收空闲区\t5、调整空闲区\n");
	printf("\n");
	printf("\t\t6、插入进程  \t7、删除进程  \t8、查看进程  \t9、保存进程  \t10、读取进程\n");
	printf("\n");	
	printf("\t\t11、执行进程  \t12、清空屏幕  \t13、退出系统\n");	
	printf("************************************************************************************************************************\n");
}
