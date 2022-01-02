# Operation-System-Partition-allocation
About operation system dynamic-partition-allocation（关于操作系统动态分区分配）

Dynamic partition allocation storage management

Establish a data structure that describes the memory allocation situation;
Establish data structures that describe the process;
Processes are generated in two ways: 
	(a) automatically, and (b) manual input;
Display the memory allocation status on the screen, the execution of each process;
Establish partition allocation and recycling algorithm, support compact algorithm;
The passage of time can be simulated in the following ways: 
	(a) press the keyboard, each press can be considered a unit of time; (b) the response WM_TIMER;
Store the execution of a batch of processes in a disk file, which can be read out and replayed later;
Supported algorithms: first-time adaptation algorithm, loop first-time adaptation algorithm, best-fit algorithm: worst-case adaptation algorithm.

动态分区分配存储管理

建立描述内存分配状况的数据结构；
建立描述进程的数据结构；
使用两种方式产生进程：（a）自动产生， （b）手工输入；
在屏幕上显示内存的分配状况、每个进程的执行情况；
建立分区的分配与回收算法，支持紧凑算法；
时间的流逝可用下面几种方法模拟：（a）按键盘，每按一次可认为过一个时间单位； (b) 响应 WM_TIMER；
将一批进程的执行情况存入磁盘文件，以后可以读出并重放；
支持算法：首次适应算法、循环首次适应算法、最佳适应算法：最坏适应算法。

