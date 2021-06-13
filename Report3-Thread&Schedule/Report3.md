# Report3



## Q1

What is a process? What is a program? And what is the difference?

说明进程与程序的区别：

>   程序是一组执行指定任务的指令，存储在磁盘上的某个文件中。程序是永存的、静态的。
>
>   进程是程序在数据集上的一次执行，可以创建和退出，是动态的，进程用被分配的地址空间执行某个程序，拥有 CPU、内存地址、磁盘、I/O等资源。



## Q2

What is job? And what is the difference between process and job?

说明进程与作业的区别：

>   进程是程序在数据集上的一次执行，可以创建和退出，是动态的，进程用被分配的地址空间执行某个程序，拥有 CPU、内存地址、磁盘、I/O等资源。进程是操作系统层面的概念。
>
>   作业是为了某种目的而提交给操作系统的一系列程序，是应用层面的概念。 作业的进行依赖至少一个进程。



## Q3

What are the differences between job scheduling and process scheduling?

说明作业调度与进程调度的区别：

>   进程调度是真正让某个就绪状态的进程获得CPU等资源变为运行状态，而作业调度只是使作业具有了运行的机会。
>
>   进程调度（又称微观调度、低级调度、短程调度）：是按照某种调度算法从就绪状态的进程中选择一个进程并给其分配CPU等资源。由内核程序进程调度程序负责进程调度 。
>
>   作业调度（又称高级调度、宏观调度、长程调度）：是按照某种调度算法从后备作业队列中选择作业装入内存运行；另外当该作业执行完毕后，还负责回收系统资源。由作业调度程序负责作业调度。
>
>   进程调度虽然是在系统内部的低级调度，但进程调度的优劣直接影响作业调度的性能。



## Q4

How many statuses are in a job(in the code for this report—scheduler)? And what are they?

本次实验作业有几种状态(在本次报告的代码中-scheduler)？请列举，并分别解释几种状态

>   三种，分别是 READY, RUNNING, DONE
>
>   READY：作业在等待列表中等待被调度
>
>   RUNNING： 作业处于运行中
>
>   DONE：作业已完成



## Q5

What programs for job control are used in this experiment? And their function?

本实验作业控制命令处理程序包括哪些？它们分别实现什么功能？

>   本实验作业控制命令处理程序包括 deq、enq、stat它们分别实现的功能：
>
>   enq：给作业调度程序发送新的作业加入作业列表请求。 输入参数 num 指定优先级（可选的，使用 -p num 范围是 0~3 的整数，默认是0），e_file 指定 可执行文件的绝对路径，args 给出传递给 e_file 的参数
>
>   deq：给作业调度程序发送指定作业从作业列表中移除请求。 输入参数 jid 指定需要移除的作业的 id
>
>   stat：给作业调度程序发送打印队列中的作业信息请求



## Q6

What is used for inter-process communication in this experiment? And its function?

本实验采用什么进行进程之间的通信？它相当于什么作用？

>   本实验采用有名管道和信号进行进程之间的通信。
>
>   有名管道用于传递添加新作业、移除作业、打印作业信息的命令和相关的信息。（从 enq、deq、stat 传递给 scheduler）
>
>   信号用于父子进程以及定时器之前交流信息。（父进程运行、暂停、终止子进程，子进程通知父进程自身终止，定时器通知父进程进行作业调度等）



## Q7

Run the job scheduler program, And analyze the execution of the submitted job:

运行作业调度程序，分析提交作业后的作业的执行过程:

>   提交作业后，该作业被加入到等待列表中。
>
>   在作业调度选择时：
>
>   1.  有且仅有该作业的优先级等于作业列表最高优先级，该作业将会被选中并运行
>   2.  该作业的优先级和其他一些作业的优先级都等于作业列表最高优先级，并且该作业等待时间最长，该作业将会被选中并运行
>   3.  其他情况则处于等待队列中，等待时间会增加，每等待100ms该作业优先级加1
>
>   当该作业完成或者被主动取消时，将会被移除作业队列。



## Q8

Understand the process of job scheduling——Submit a new job (Execution results and corresponding code)：

Schedueler作业调度的过程理解——提交新作业 （分析执行结果及代码表现）：

>   当scheduler收到新作业提交请求，其根据提交参数(defpri, owner等)构建新作业，并且分配作业ID、设置作业状态为READY，初始化作业create_time、wait_time、run_time，然后将新作业加入到作业等待列表中，使用fork,exev创建一个执行该作业任务的进程并将其暂停，将新进程PID记录在作业信息中。
>
>    代码表现（含注释）：
>
>   ```c
>       ......
>       //  根据提交参数(defpri, owner等)构建新作业
>   
>       newjob = (struct jobinfo *) malloc(sizeof(struct jobinfo));
>       newjob->jid = allocjid(); // 分配作业ID
>       newjob->defpri = enqcmd.defpri; // 根据 defpri 设定默认优先级
>       newjob->curpri = enqcmd.defpri;  // 根据 defpri 设定当前优先级
>       newjob->ownerid = enqcmd.owner;
>       newjob->state = READY; // 初始化作业状态为 READY
>       newjob->create_time = time(NULL); // 初始化作业创建时间
>       newjob->wait_time = 0;
>       newjob->run_time = 0;
>       arglist = (char **) malloc(sizeof(char *) * (enqcmd.argnum + 1));
>       newjob->cmdarg = arglist;
>       offset = enqcmd.data;
>       argvec = enqcmd.data;
>       while (i < enqcmd.argnum) { // 解析输入命令参数
>           if (*offset == ':') {
>               *offset++ = '\0';
>               q = (char *) malloc(offset - argvec);
>               strcpy(q, argvec);
>               arglist[i++] = q;
>               argvec = offset;
>           } else
>               offset++;
>       }
>       arglist[i] = NULL;
>   
>       // 加入新作业到作业队列
>       newnode = (struct waitqueue *) malloc(sizeof(struct waitqueue));
>       newnode->next = NULL;
>       newnode->job = newjob;
>       if (head) {
>           for (p = head; p->next != NULL; p = p->next);
>           p->next = newnode;
>       } else
>           head = newnode;
>       //  为作业创建进程
>       if ((pid = fork()) < 0)
>           error_sys("enq fork failed");
>       /* In child process */
>       if (pid == 0) {
>           newjob->pid = getpid();
>           //  阻塞子进程，将其暂停
>           raise(SIGSTOP);
>           /* dup the globalfile descriptor to stdout */
>           dup2(globalfd, 1);
>           if (execv(arglist[0], arglist) < 0)
>               printf("exec failed\n");
>           exit(1);
>       } else {
>           waitpid(pid, NULL, 0);
>           newjob->pid = pid; //  将新进程PID记录在作业信息中
>           printf("\n    new job: jid=%d, pid=%d\n", newjob->jid, newjob->pid);
>       }
>   ```
>
>   



## Q9

Understand the process of job scheduling——End of job execution (Execution results and corresponding code)： 

Schedueler作业调度的过程理解——作业正常执行结束 （分析执行结果及代码表现）：

>   作业正常结束时，schedueler 会收到执行该作业任务的进程发送的 SIGCHLD 信号，使用 WIFEXITED(status) 返回值判断作业正常结束，然后将该作业状态更新为 DONE，并打印输出作业完成的语句。之后的进程调度会将该作业移出执行列表。
>
>   代码表现（含注释）：
>
>   ```c
>   void sig_handler(int sig, siginfo_t *info, void *notused) {
>   
>       int status;
>       int ret;
>       switch (sig) {
>           case SIGVTALRM :
>               schedule(); // 进行作业调度
>               return;
>           case SIGCHLD :
>               ret = waitpid(-1, &status, WNOHANG);
>               if (ret == 0 || ret == -1)
>                   return;
>               if (WIFEXITED(status)) // 判断作业正常结束
>               {
>                   current->job->state = DONE; // 更新作业状态为 DONE
>                   printf("normal termation, exit status =%d\t    jid =%d, pid =%d\n\n",
>                          WEXITSTATUS(status), current->job->jid, current->job->pid); // 打印输出作业完成的语句
>               }
>   
>               if (wait_free) {
>                   if (WIFSIGNALED(status)) {
>                       printf("abnormal termation, signal number =%d\t    jid =%d, pid =%d\n\n",
>                              WTERMSIG(status), wait_free->job->jid, wait_free->job->pid);
>                   } else if (WIFSTOPPED(status)) {
>                       printf("child stopped, signal number =%d\t    jid =%d, pid =%d\n\n",
>                              WSTOPSIG(status), wait_free->job->jid, wait_free->job->pid);
>                   }
>                   free_select(wait_free);
>               }
>               return;
>           default :
>               return;
>       }
>   }
>   
>   void jobswitch() {
>   
>       struct waitqueue *p;
>       int i;
>       if (current && current->job->state == DONE) {                   /* current job finished */
>           // current作业完成，移出作业列表
>           for (i = 0; (current->job->cmdarg)[i] != NULL; i++) {
>               free((current->job->cmdarg)[i]);
>               (current->job->cmdarg)[i] = NULL;
>           }
>   
>           free(current->job->cmdarg);
>           free(current->job);
>           free(current);
>           current = NULL;
>       }
>       ......
>   }
>   ```
>
>   



## Q10

Understand the process of job scheduling——job scheduling due to Priority(Execution results and corresponding code)：

Schedueler作业调度的过程理解——因为优先级和进行作业调度（分析执行结果及代码表现）：

>   在每隔100ms,scheduler收到 SIGVTALRM 信号，触发 schedule() 函数的执行，在其中调用 jobselect(), 遍历所有作业, 选择优先级最高优先级（优先级同处最高则从中选等待时间最长）的作业,并将其指定为下一个时间片执行的作业。
>
>   代码表现（含注释）：
>
>   ```c
>   void sig_handler(int sig, siginfo_t *info, void *notused) {
>       int status;
>       int ret;
>   
>       switch (sig) {
>           case SIGVTALRM :
>               schedule(); // 收到 SIGVTALRM 信号，触发 schedule() 函数的执行
>               return;
>   ......
>   ```
>
>   ```c
>   void schedule() {
>   ......
>   
>       next = jobselect(); // 调用 jobselect() 选择下一个时间片执行的作业
>   
>   ......
>   ```
>
>   ```c
>   struct waitqueue *jobselect() {
>   
>       struct waitqueue *p, *prev, *select, *selectprev;
>   
>       int highest = -1;
>       select = NULL;
>       selectprev = NULL;
>   
>       if (head) {
>           for (prev = head, p = head; p != NULL; prev = p, p = p->next) {
>   
>               if (p->job->curpri > highest) { // 选择优先级最高优先级的作业
>                   select = p;
>                   selectprev = prev;
>                   highest = p->job->curpri;
>               } else if (p->job->curpri == highest &&
>                          p->job->wait_time > select->job->wait_time) { // 优先级同处最高则从中选等待时间最长
>                   select = p;
>                   selectprev = prev;
>               }
>           }
>   
>           if (current && current->job->curpri > select->job->curpri) {
>               return NULL;
>           }
>   
>           // 将选出的作业移出等待队列
>           selectprev->next = select->next;
>           if (select == selectprev) {
>               if (select->next != NULL) {
>                   head = head->next;
>                   select->next = NULL;
>               } else {
>                   head = NULL;
>               }
>           }
>       }
>       return select;
>   }
>   ```
>
>   





## Q11

Understand the process of job scheduling——Job scheduling due to time slice (Execution results and corresponding code)：

Schedueler作业调度的过程理解——因为时间片而进行作业调度（分析执行结果及代码表现）：

>   程序中指定时间片为100ms. 在作业执行过程中，在100ms内,如果作业自己结束或者收到作业取消的命令，作业终止，否则作业一直在执行直到用完 100 ms，之后,作业会被暂停, scheduler重新选择下一个时间片执行的作业然后让新选择的作业继续执行.
>
>   代码表现（含注释）：
>
>   ```c
>       ......
>   
>       sigaction(SIGVTALRM, &newact, &oldact2);
>   
>       /* timer interval: 0s, 100ms */
>       interval.tv_sec = 0;
>       interval.tv_usec = 100000; // 100000 μs = 100 ms
>       
>       new.it_interval = interval;
>       new.it_value = interval;
>       setitimer(ITIMER_VIRTUAL, &new, &old);
>       
>       ......
>   ```
>
>   ```c
>   void sig_handler(int sig, siginfo_t *info, void *notused) {
>       int status;
>       int ret;
>   
>       switch (sig) {
>           case SIGVTALRM :
>               schedule(); // 收到 SIGVTALRM 信号，触发 schedule() 函数的执行
>               return;
>   ......
>   ```

