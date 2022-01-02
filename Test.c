#include "test.h"

int main()
{
	Process* process_head = Process_head();
	Partition* partition_head = Partition_head();
	int _select, _num;
	char _name[20];
	Print_menu();

	while (1) {
		printf("###>");
		scanf("%d", &_select);

		switch (_select)
		{
		case 1:
			printf("�����������Ŀ��");
			scanf("%d", &_num);
			Partition_insert(partition_head, _num);
			break;
		case 2:
			printf("����������������ƣ�");
			scanf("%s", _name);
			printf("���䷽ʽ��1��FFA��2��NFA��3��BFA��4��WFA����");
			scanf("%d", &_select);
			switch (_select)
			{
			case 1:
				FFA(partition_head, process_head, _name);
				break;
			case 2:
				NFA(partition_head, process_head, _name);
				break;
			case 3:
				BFA(partition_head, process_head, _name);
				break;
			case 4:
				WFA(partition_head, process_head, _name);
				break;
			default:
				printf("ERROR\n");
				break;
			}
			break;
		case 3:
			Print_partition(partition_head);
			break;
		case 4:
			Recycle(partition_head, process_head);
			break;
		case 5:
			Adjust(partition_head, process_head);
			break;
		case 6:
			printf("���������Ŀ��");
			scanf("%d", &_num);
			Process_insert(process_head, _num);
			break;
		case 7:
			printf("ɾ���������ƣ�");
			scanf("%s", _name);
			Process_delete(process_head, _name);
			break;
		case 8:
			Print_process(process_head);
			break;
		case 9:
			printf("����������ƣ�");
			scanf("%s", _name);
			Process_save(process_head, _name);
			break;
		case 10:
			Process_produce_fromfile(process_head);
			break;
		case 11:
			printf("ִ�н������ƣ�");
			scanf("%s", _name);
			Process_excute(process_head, _name);
			break;
		case 12:
			system("cls");
			Print_menu();
			break;
		case 13:
			exit(0);
			break;
		default:
			break;
		}
	}
}
