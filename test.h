#include "partition.h"


void Process_insert(Process* process_head, int process_num) {
	int i, _start, _size, _excute_time;
	char _name[20];
	Process* current = process_head;

	while (i < process_num) {
		Process* _new = (Process*)malloc(sizeof(Process));
		printf("�������ƣ�");
		scanf("%s", _name);
		printf("���̴�С��");
		scanf("%d", &_size);
		printf("ִ��ʱ�䣺");
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
	printf("\t��������\t��ʼλ��\t���̴�С\tִ��ʱ��\t����״̬\n");
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
			printf("����״̬\n");
			break;
		case 2:
			printf("����״̬\n");
			break;		
		case 3:
			printf("����״̬\n");
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
		printf("���������ƣ�");
		scanf("%s", _name);
		printf("��ʼλ�ã�");
		scanf("%d", &_start);
		printf("�����С��");
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
	printf("\t\t\t����������\t��ʼλ��\t���䳤��\n");
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
	printf("\t\t1�����������\t2�����������\t3���鿴������\t4�����տ�����\t5������������\n");
	printf("\n");
	printf("\t\t6���������  \t7��ɾ������  \t8���鿴����  \t9���������  \t10����ȡ����\n");
	printf("\n");	
	printf("\t\t11��ִ�н���  \t12�������Ļ  \t13���˳�ϵͳ\n");	
	printf("************************************************************************************************************************\n");
}
