# Report2



## Q1

[code for report2.zip](code%20for%20report2.zip)

These are codes for report2. If you find bugs in it, just fix them.

You don't need to answer this question. 你不需要回答本问题。



## Q2

What is a system call:

什么是系统调用：

>   系统调用是一个函数调用，由内核公开，抽象掉最底层的细节，提供进程和操作系统之间的接口，允许用户级进程请求操作系统的服务。



## Q3

What is fork:

简述fork调用:

>   fork() 是UNIX或类UNIX中的分叉函数，fork函数将运行着的程序分成2个几乎完全一样的进程，每个进程都启动一个从代码的同一位置开始执行的线程。
>
>   fork 调用的返回值是负值时表示创建子进程失败，是零时返回到新创建的子进程，是正值时返回父进程或调用者，该正值代表子进程的PID。



## Q4

How to realize inter-process communication:

如何实现进程间的通信:

>   可以通过以下方式实现进程间的通信：
>
>   1.  管道： 有普通管道、流管道、命名管道，普通管道数据只能单向流动，而且只能在具有亲缘关系（ 通常是指父子进程关系 ）的进程间使用，流管道数据可以双向传输，命名管道的数据传输可以为单向或双向，允许无亲缘关系进程间的通信
>
>   2.  消息队列： 消息组成的链表，存放在内核中并由消息队列标识符标识
>
>   3.  信号量： 一个计数器，可以用来控制多个进程对共享资源的访问，常作为一种锁机制，防止某进程正在访问共享资源时，其他进程也访问该资源
>
>   4.  共享存储： 允许两个或多个进程共享一个给定的存储区
>
>   5.  套接字： 对网络中不同主机上的应用进程之间进行双向通信的端点的抽象
>
>   6.  信号： 一种处理异步事件的方式，用于通知接收进程某个事件已经发生





## Q5

How to realize inter-process connection:

如何实现进程间的连接:

>   可以通过有名管道(named pipe或FIFO)实现进程间的连接。
>
>   有名管道提供了一个路径名与之关联，以 FIFO 的文件形式存在于文件系统中，它将两个进程连接起来。



## Q6

Write the prototype of function "fork":

写出函数"fork"的原型:

>   pid_t fork( void);



## Q7

Write the prototype of function "signal":

写出函数"signal"的原型:

>   void (*signal(int sig, void (*func)(int)))(int);



## Q8

Write the prototype of function "pipe":

写出函数"pipe"的原型:

>   int pipe (int pipedes[2]);



## Q9

 Write the prototype of function "tcsetpgrp":

写出函数"tcsetpgrp"的原型:

>   int tcsetpgrp (int fd, pid_t pgrp_id);



## Q10

Execute "fork.c" and observe, please describe the result (not execution result)：

运行" fork.c ", 观察结果并简述结果（描述执行结果，和出现该结果的原因）：

>   执行结果： 在控制台输出了与执行命令 "/bin/ls -l /" 得到的内容相同的结果，即使用长列表格式输出根目录(/)内容列表。
>
>   
>
>   出现该结果的原因：和控制台输出有关的关键代码是子进程 printf 函数调用 和 execvp 函数调用，调用 printf 函数时将内容输出至输出缓存区但是没有刷新到控制台。之后调用 execvp 函数，其将可执行文件 "/bin/ls" 的内容（以及 execvp 的传参）取代调用进程的内容（包括代码段，数据段和堆栈等），所以最终在控制台只看到了执行命令 "/bin/ls -l /" 输出的内容。
>
>   
>
>   fork.c 中的问题，printf结果为何没打印，应该如何修改： 因为调用 printf 函数时将内容输出至输出缓存区但是没有刷新到控制台，并且立即调用了 execvp 函数修改了进程的内容。 可以在调用 printf 函数之后立即调用函数 fflush(stdout); 刷新输出缓存去到控制台。



## Q11

Execute "fork.c" and observe, please describe how to distinguish between parent and child processes in a program：


运行" fork.c ", 观察结果，并简述程序中如何区分父进程和子进程：

>   执行结果： 在控制台输出了与执行命令 "/bin/ls -l /" 得到的内容相同的结果，即使用长列表格式输出根目录(/)内容列表。（子进程调用 printf 函数以及 execvp 函数（执行ls命令），父进程调用 waitpid 函数，等待子进程执行结束）
>
>   
>
>   如何区分父进程和子进程： 通过 fork 调用的返回值来区分，如果得到返回值为 0 的进程为子进程，得到返回值不为 0 的进程为父进程（负值时表示创建子进程失败，正值代表创建的子进程的PID）。



## Q12

Execute "pipe.c" and observe, please describe the result (not execution result)：

运行" pipe.c", 观察结果并简述结果（ 描述执行结果，和出现该结果的原因 ）：

>   执行结果： 父进程创建管道并产生 ls子进程 和 more子进程 。 控制台上先输出了父进程与 ls子进程 通过管道互发消息相关的内容，然后输出了与执行命令 "ls -l /etc/ | more" 得到的内容相同的结果，即使用 more 指令 查看/etc/目录下的长列表格式内容列表。
>
>
>   出现该结果的原因：父进程创建管道并产生 ls子进程 ， ls子进程 先阻塞在从管道读数据等待父进程写入数据。 然后父进程创建 more子进程 ，将管道的读描述符复制给标准输入，并执行 more 命令。 同时父进程通过管道给 ls子进程 发送数据使得 ls子进程 不阻塞， ls子进程 读出管道数据之后在控制台输出了数据，并将管道的写描述符复制给标准输出，然后执行 ls 命令。ls 命令的结果从标准输出被重定向管道的输入， more 命令的数据来源从标准输入被重定向到管道的输出，所以子进程之间通过管道实现了通信。 



## Q13

Execute "pipe.c" and observe. Is execvp(prog2_argv[0],prog2_argv)(Line 56) executed? And why? :

运行" pipe.c", 观察结果。execvp(prog2_argv[0],prog2_argv)（第56行）是否一定会执行，为什么

>   不一定。
>
>   因为如果父进程创建管道或者创建子进程失败，程序直接退出 execvp(prog2_argv[0],prog2_argv) 将不会执行。



## Q14

Execute "signal.c" and observe, please describe the result (not execution result)：

运行" signal.c", 观察结果并简述结果（ 描述执行结果，和出现该结果的原因 ）：

>   执行结果：父进程和子进程每隔一秒都在控制台打印自己的 PID
>
>   出现该结果的原因：父进程和子进程处于死循环中，并且没有收到任何外部发来的信号



## Q15

Execute "signal.c" and observe. Please answer, how to execute function ChildHandler? : 

运行" signal.c", 观察结果。请回答，怎样让函数ChildHandler执行？

>   可以通过以下方式让函数ChildHandler执行
>
>   1.  向父进程或者子进程发送 SIGCHLD 信号，可以使用命令 kill -17 \<PID\> 实现
>   2.  向子进程发送进程退出信号，比如 SIGILL信号，SIGKILL信号，可以使用命令 kill -4 \<PID\>，kill -9 \<PID\>， 实现



## Q16

Execute "process.c" and observe, please describe the result (not execution result)：


运行" process.c", 观察结果并简述结果（ 描述执行结果，和出现该结果的原因 ）：

>   执行结果： 父子进程分别在控制台打印了自己的 PID, 最终子进程退出，父进程被挂起。
>
>
>   出现该结果的原因： 父进程在打印了了自己的 PID 之后，将子进程放入新的进程组并设置控制终端为子进程拥有，然后等待子进程结束。 子进程所在的进程组成为前台进程组后，子进程执行 execvp("/bin/vi","vi",NULL) 但是没有生效（可以改为 execlp("/bin/vi","vi",NULL) 使其生效），然后子进程结束。子进程结束后，父进程尝试将其所在的进程组设为前台进程组，然后被挂起。 



## Q17

Execute "process.c" and observe. Please answer, how many ./process in the process list? And what’s the difference between them?:

运行" process.c", 观察结果。请回答，进程列表中有几个./process，区别在哪里：

>   刚开始的时候有两个，分别是父子进程，他们的PID不同，此时他们均处于 TASK_RUNNING 状态。
>
>
>   如果父进程先执行了 tcsetpgrp 函数，子进程所在的进程组为前台进程组，子进程可以正常地执行完后面的代码然后结束进程，父进程在后台等待子进程结束的过程中处于 TASK_INTERRUPTIBLE+ 状态，子进程结束后变为 TASK_RUNNING 状态， 然后 处于后台的父进程尝试调用 tcsetpgrp 函数状态变为 TASK_STOPPED 。
>
>
>   如果子进程先执行了 tcsetpgrp 函数，子进程将会处于 TASK_STOPPED 状态，而之后父进程在前台等待子进程结束而处于 TASK_INTERRUPTIBLE 状态。



## Q18

Execute "process.c" and observe. Please answer, what happens after killing the main process:

运行" process.c", 观察结果。请回答，杀死主进程后，出现什么情况并分析原因：

>   如果运行程序之后不退出子进程调用的vi命令窗口，直接结束父进程，子进程会进入 TASK_INTERRUPTIBLE 状态。
>
>   出现这种情况的原因是 子进程 vi 得不到控制台标准输入。
>
>   当修改程序使得父进程成功回显输入字符之后，如果输入一些字符在按下回车键之前使用kill命令结束父进程，此时父进程退出，刚刚输入的这些字符将会出现在运行该父进程的 bash 的命令行中。
>
>   出现这种情况的原因是输入的字符保留在输入缓冲区中，并没有被父进程读取。



