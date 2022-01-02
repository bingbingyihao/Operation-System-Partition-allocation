#include "process.h"


Partition* Partition_head() {
	Partition* head = (Partition*)malloc(sizeof(Partition));

	strcpy(head->name, "");
	head->size = 0;
	head->start = 0;
	head->next = NULL;

	return head;
}

void New_insert(Partition* partition_head, int _start, int _size) {
	Partition* current = partition_head;
	Partition* _new = (Partition*)malloc(sizeof(Partition));

	strcpy(_new->name, "NEW");
	_new->start = _start;
	_new->size = _size;
	_new->next = NULL;
	while (current->next != NULL && current->start + current->size < _start)
		current = current->next;
	_new->next = current->next;
	current->next = _new;
}

void Partition_delete(Partition* partition_head, char* _name) {
	Partition* current = partition_head->next, * current_last = partition_head;

	while (current) {
		if (strcmp(current->name, _name) == 0) {
			current_last->next = current->next;
			break;
		}
		current_last = current;
		current = current->next;
	}
}

void Adjust(Partition* partition_head, Process* process_head) {
	Process* current_process = process_head->next;
	Partition* current_partition = partition_head->next;
	int process_sumlength = 0;
	if (current_process) {
		current_process->start = 0;
		process_sumlength = current_process->size;
	}

	while (current_process->next) {
		current_process->next->start = current_process->start + current_process->size;
		process_sumlength += current_process->next->size;
		current_process = current_process->next;
	}

	int _new_partition_start = process_sumlength, _new_partition_size = current_partition->size;

	while (current_partition->next)
	{
		_new_partition_size += current_partition->next->size;
		current_partition = current_partition->next;
	}

	Partition* _new = (Partition*)malloc(sizeof(Partition));
	strcpy(_new->name, "NEW");
	_new->start = _new_partition_start;
	_new->size = _new_partition_size;
	_new->next = NULL;
	partition_head->next = _new;
}

void Recycle(Partition* partition_head, Process* process_head) {
	Process* current_process = process_head->next;
	Partition* current_partition = partition_head->next;

	while (current_process) {
		if (current_process->status == 3) {
			while (current_partition)
			{
				if (current_partition->start + current_partition->size == current_process->start) {
					current_partition->size += current_process->size;
					Process_delete(process_head, current_process->name);
					break;
				}
				if (current_partition->start == current_process->start + current_process->size) {
					current_partition->size += current_process->size;
					current_partition->start = current_process->start;
					Process_delete(process_head, current_process->name);
					break;
				}
				if (current_partition->start + current_partition->size != current_process->start &&
					current_partition->start != current_process->start + current_process->size) {
					New_insert(partition_head, current_process->start, current_process->size);
					Process_delete(process_head, current_process->name);
					break;
				}
				current_partition = current_partition->next;
			}
			//break;
		}
		current_process = current_process->next;
	}
}

void FFA(Partition* partition_head, Process* process_head, char* _name) {
	Partition* current_partition = partition_head->next;
	Process* current_process = process_head->next;
	int _is_adjust_flag = 0;

	while (current_process) {
		if (strcmp(current_process->name, _name) == 0 && current_process->status == 1) {
			while (current_partition)
			{
				if (current_partition->size >= current_process->size) {
					_is_adjust_flag = 1;
					break;
				}
				current_partition = current_partition->next;
			}
			if (!_is_adjust_flag)
			{
				Adjust(partition_head, process_head);

				current_partition = partition_head->next;
				if (current_partition->size < current_process->size)
					return;
			}

			current_partition = partition_head->next;
			while (current_partition) {
				if (current_partition->size >= current_process->size) {
					current_partition->size -= current_process->size;
					current_process->start = current_partition->start;
					current_process->status = 2;
					partition_head->start = current_partition->start + current_process->size;

					if (current_partition->size == 0) {
						Partition_delete(partition_head, current_partition->name);
						break;
					}
					current_partition->start += current_process->size;
					break;
				}
				current_partition = current_partition->next;
			}
			break;
		}
		current_process = current_process->next;
	}
}

void NFA(Partition* partition_head, Process* process_head, char* _name) {
	int _start = partition_head->start;
	Partition* current_partition = partition_head->next;
	Process* current_process = process_head->next;
	int _is_adjust_flag = 0;

	while (current_process) {
		if (strcmp(current_process->name, _name) == 0  && current_process->status == 1) {
			while (current_partition)
			{
				if (current_partition->size >= current_process->size) {
					_is_adjust_flag = 1;
					break;
				}
				current_partition = current_partition->next;
			}
			if (!_is_adjust_flag) {
				Adjust(partition_head, process_head);

				current_partition = partition_head->next;
				if (current_partition->size < current_process->size)
					return;
			}

			current_partition = partition_head->next;
			while (current_partition) {
				if ((current_partition->size >= current_process->size) && current_partition->start > _start) {
					current_partition->size -= current_process->size;
					current_process->start = current_partition->start;
					current_process->status = 2;
					partition_head->start = current_partition->start + current_process->size;

					if (current_partition->size == 0) {
						Partition_delete(partition_head, current_partition->name);
						break;
					}
					current_partition->start += current_process->size;
					return;
				}
				current_partition = current_partition->next;
			}

			current_partition = partition_head->next;
			while (current_partition) {
				if ((current_partition->size >= current_process->size) && current_partition->start <= _start) {
					current_partition->size -= current_process->size;
					current_process->start = current_partition->start;
					current_process->status = 2;
					partition_head->start = current_partition->start + current_process->size;

					if (current_partition->size == 0) {
						Partition_delete(partition_head, current_partition->name);
						break;
					}
					current_partition->start += current_process->size;
					break;
				}
				current_partition = current_partition->next;
			}
			break;
		}
		current_process = current_process->next;
	}
}

void BFA(Partition* partition_head, Process* process_head, char* _name) {
	Partition* current_partition = partition_head->next;
	Process* current_process = process_head->next;
	int min, _is_adjust_flag = 0;

	while (current_process) {
		if (strcmp(current_process->name, _name) == 0  && current_process->status == 1) {
			while (current_partition)
			{
				if (current_partition->size >= current_process->size) {
					_is_adjust_flag = 1;
					break;
				}
				current_partition = current_partition->next;
			}
			if (!_is_adjust_flag)
				Adjust(partition_head, process_head);

			current_partition = partition_head->next;
			while (current_partition) {
				min = current_partition->size - current_process->size;
				if (min >= 0)
					break;
				current_partition = current_partition->next;
			}

			if (min < 0)
				exit(-1);

			while (current_partition) {
				int temp = current_partition->size - current_process->size;
				if (temp >= 0 && temp < min) {
					min = temp;
				}
				current_partition = current_partition->next;
			}

			current_partition = partition_head->next;
			while (current_partition) {
				if ((current_partition->size - current_process->size) == min) {
					current_partition->size -= current_process->size;
					current_process->start = current_partition->start;
					current_process->status = 2;
					partition_head->start = current_partition->start + current_process->size;

					if (current_partition->size == 0) {
						Partition_delete(partition_head, current_partition->name);
						break;
					}
					current_partition->start += current_process->size;
					break;
				}
				current_partition = current_partition->next;
			}
			break;
		}
		current_process = current_process->next;
	}
}

void WFA(Partition* partition_head, Process* process_head, char* _name) {
	Partition* current_partition = partition_head->next;
	Process* current_process = process_head->next;
	int max, _is_adjust_flag = 0;

	while (current_process) {
		if (strcmp(current_process->name, _name) == 0  && current_process->status == 1) {
			while (current_partition)
			{
				if (current_partition->size >= current_process->size) {
					_is_adjust_flag = 1;
					break;
				}
				current_partition = current_partition->next;
			}
			if (!_is_adjust_flag)
				Adjust(partition_head, process_head);

			current_partition = partition_head->next;
			while (current_partition) {
				max = current_partition->size - current_process->size;
				if (max >= 0)
					break;
				current_partition = current_partition->next;
			}

			if (max < 0)
				exit(-1);

			while (current_partition) {
				int temp = current_partition->size - current_process->size;
				if (temp > max) {
					max = temp;
				}
				current_partition = current_partition->next;
			}

			current_partition = partition_head->next;
			while (current_partition) {
				if ((current_partition->size - current_process->size) == max) {
					current_partition->size -= current_process->size;
					current_process->start = current_partition->start;
					current_process->status = 2;
					partition_head->start = current_partition->start + current_process->size;

					if (current_partition->size == 0) {
						Partition_delete(partition_head, current_partition->name);
						break;
					}
					current_partition->start += current_process->size;
					break;
				}
				current_partition = current_partition->next;
			}
			break;
		}
		current_process = current_process->next;
	}
}
