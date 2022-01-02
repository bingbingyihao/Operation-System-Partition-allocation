#include "def.h"

Process* Process_head() {
	Process* process_head = (Process*)malloc(sizeof(Process));

	process_head->start = 0;
	process_head->size = 0;
	process_head->excute_time = 0;
	process_head->status = 1;
	strcpy(process_head->name, "");
	process_head->next = NULL;

	return process_head;
}

int Get_process_num(Process* process_head) {
	int num = 0;
	Process* current = process_head->next;

	while (current) {
		num++;
		current = current->next;
	}
	return num;
}

/*
调用键盘监听函数_kbhit，_getch获取按键值，按键为“ESC”时退出
*/
void Process_excute(Process* process_head, char* _name) {
	Process* current = process_head->next;
	int ch;

	while (current) {
		if (strcmp(current->name, _name)==0 && current->status == 2) {			
			while (1) {
				if (_kbhit()) {
					ch = _getch();
					if (ch == 27)
						break;
					current->excute_time--;
				}
				if (current->excute_time <= 0) {
					current->status = 3;
					break;
				}
			}
			break;
		}
		current = current->next;
	}
}

void Process_save(Process* process_head, char* _name) {
	Process* current = process_head->next;
	char _current_name[20], _size[20], _excute_time[20];
	char _t[4] = "\t\t";

	while (current) {
		if (strcmp(current->name, _name) == 0) {
			FILE* fp = NULL;

			fp = fopen("test.txt", "a");

			strcpy(_current_name, current->name);
			strcat(_current_name, _t);
			fprintf(fp, _current_name);

			itoa(current->size, _size, 10);
			strcat(_size, _t);
			fprintf(fp, _size);

			itoa(current->excute_time, _excute_time, 10);
			strcat(_excute_time, _t);
			fprintf(fp, _excute_time);

			switch (current->status)
			{
			case 1:
				fprintf(fp, "创建状态\n");
				break;
			case 2:
				fprintf(fp, "就绪状态\n");
				break;			
			case 3:
				fprintf(fp, "阻塞状态\n");
				break;		
			default:
				fprintf(fp, "ERROR\n");
				break;
			}

			fclose(fp);
			break;
		}
		current = current->next;
	}
}

void Process_produce_fromfile(Process* process_head) {
	FILE* fp = NULL;
	int flag, file_row = 0;
	fp = fopen("test.txt", "r");
	while (!feof(fp))
	{
		flag = fgetc(fp);
		if (flag == '\n')
			file_row++;
	}
	fclose(fp);

	fp = fopen("test.txt", "r");
	Process* current = process_head;
	char _current_name[20], _size[20], _excute_time[20], _status[20];
	int i = 0;

	while (i < file_row) {
		Process* _new = (Process*)malloc(sizeof(Process));

		fscanf(fp, "%s", _current_name);
		fscanf(fp, "%s", _size);
		fscanf(fp, "%s", _excute_time);
		fscanf(fp, "%s", _status);

		strcpy(_new->name, _current_name);
		_new->start = -1;
		_new->size = atoi(_size);
		_new->excute_time = atoi(_excute_time);
		_new->status = 1;
		_new->next = NULL;

		while (current->next != NULL)
			current = current->next;
		current->next = _new;

		i++;
	}
	fclose(fp);
}

void Process_delete(Process* process_head, char* _name) {
	Process* current = process_head->next, * current_last = process_head;

	while (current) {
		if (strcmp(current->name, _name) == 0) {
			current_last->next = current->next;
			break;
		}
		current_last = current;
		current = current->next;
	}
}
