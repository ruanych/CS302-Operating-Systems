# Submit

| Content    | File | Grades | Remarks |
| ---------- | ------ | ------ | ------ |
| Report | [Report5.md](./Report5.md) | 60/60  |  |
| Code | [Banker.cpp](./Banker.cpp) | 30/40 | The logic of the arrival of the new request is not processed correctly, the fixed version [Banker_fixed.cpp](./Banker_fixed.cpp)  |

<br>

# Banker Task

Please submit "Banker.cpp".

You are asked to implement a Banker’s Algorithm, your code will be judged by standard test case.

language: C++, you are free to use all STL



**Input**:

First line is an integer r, which is the number of resource_remain types.

The second line will be r integers, which are the maximum quantity of each resource_remain.

Then will be following a list of commands. The commands are in three form:

New process registering, such as “1678 new 6 5 0 7”, means process 1678 is a new process, whose maximum need of each resource_remain is 6 5 0 7 (assume r is 4)

Resource requesting, such as “233 request 0 4 5 3”, means process 233 is an old process, it request more resource_remain, the need of each resource_remain is 0 4 5 3.

Process termination, such as “233 terminate”, means process 233 terminate and return all resources it holding.

**Output**:

For each command, output “OK” or “NOT OK” to determine if the command can execute. If OK, execute the command.


补充：

New:

进程号已经存在，NOT OK

maximum need > maximum quantity of each resource_remain, NOT OK


Request:

新请求>remain, NOT OK

新请求>need, NOT OK

新请求满足后不safe, NOT OK

进程不存在, NOT OK

注：进程需求满足后仍然hold资源，不会自动释放


Terminate：

进程不存在, NOT OK