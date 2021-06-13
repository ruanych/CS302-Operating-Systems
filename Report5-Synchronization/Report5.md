# Report5



## Q1

What is deadlock?

>   死锁是指多个进程在执行过程中，由于竞争资源进入循环等待资源的状态而造成的一种阻塞的现象，如果没有外力的作用，它们都将无法推进下去。



## Q2

What are the requirements of deadlock?

>   如果在一个系统中以下四个条件同时成立，那么就能引起死锁:
>
>   1.  互斥(mutual exclusion)：至少有一个资源必须处于非共享模式，即一次只能有一个进程使用它。如果另一个进程申请这个资源，那么该申请进程应等到该资源释放为止。
>   2.  占有并等待(hold and wait): 一个进程应占有至少一个资源，并等待另一个资源，而该资源被其他进程所占有。
>   3.  非抢占(no preemption): 资源不能被抢占，即资源只能被获得该资源的进程在完成任务后主动释放。
>   4.  循环等待(circular wait):有一组等待进程{P0, P1,..., Pn}, P0等待的资源被P1占有，P1等待的资源被P2占有，.....，P(n-1)等待的资源被Pn占有，Pn 等待的资源被P0占有。



## Q3

What’s different between deadlock prevention and deadlock avoidance?

>   死锁预防（deadlock prevention）方法设计不同的资源分配算法，来保证不发生死锁，具体的做法是确保至少有一个必要条件（本报告中的问题2中的四个条件）不成立。
>
>   死锁避免（deadlock avoidance）要求操作系统事先得到相关进程申请资源和使用资源等额外信息，通过这些额外信息，在系统运行过程中，对进程提出的每一个（系统能够满足的）资源申请进行检查，根据检查结果决定是否分配资源，若分配后系统可能发生死锁，则不予分配，否则予以分配。系统应考虑：现有的可用资源、已分配给每个进程的资源及每个进程将来申请和释放的资源。
>
>   死锁预防不需要得到相关进程申请资源和使用资源等额外信息，也不需要在资源申请时进行检测，但可能会出现一些其他问题（比如破坏非抢占条件，资源可被抢占会导致线程需要再次申请被强占的资源，系统效率降低）。而死锁避免需要得到相关进程申请资源和使用资源等额外信息并且在资源申请时进行检测，四个死锁条件都发生之前，系统效率不会受到影响。



## Q4

How to prevent deadlock? Give at least two examples.

>   预防死锁可以通过确保至少有一个必要条件（本报告中的问题2中的四个条件）不成立来实现。
>
>   例子
>
>   1.  破坏占有并等待条件： 系统要求所有进程一次性地申请其在整个运行过程中需要的所有资源。如果系统有足够的资源，则全部分配，否则让其等待直到有足够的资源，在等待时不持有任何资源。
>   2.  破坏非抢占条件： 如果一个已经拥有资源的进程提出了新的资源需求，并且不能系统资源不足该进程的申请无法立即得到满足，那么它必须释放它已经拥有的所有资源。之后需要时再重新申请所需的资源。
>   3.  破坏循环等待条件： 系统将所有资源按一定规则排序，所有进程对资源的请求必须严格按照这个顺序提出。



## Q5

Which way does recent UNIX OS choose to deal with deadlock problem, why?

>   UNIX 操作系统使用鸵鸟算法，即忽略死锁发生的存在，让用户手动干预死锁发生的情况。
>
>   原因：解决死锁问题的代价很高，并且发生死锁的概率较低，对待死锁不采取任何措施会获得更高的性能和效率。



## Q6

What data structures you use in your implementation（of Banker's algorithm）? Where and why you use them? Are they optimal for your purpose?

>   1.  使用的数据结构： string，unordered\_map<int, int \*>，unordered_map<int, int \*>::const\_iterator
>
>   2.  使用的目的： 
>       string 读取、识别、存储命令; 
>       unordered\_map<int, int \*> 存储进程和资源相关的信息（进程对资源的最大需求量、进程已被分配的资源量，进程ID作为key，资源量作为 value）; 
>       unordered\_map<int, int \*>::const_iterator 访问 unordered\_map 中的数据。
>
>   3.  命令是一个字符串，在 C/C++ 中可以使用 char* 或者 string， 我认为 string 更方便操作（字符串的输入读取、存储、比较），优于 char*; 
>       unordered\_map可以实现进程信息通过PID的 O(1) 查找，比其他的数据结构更方便;
>       unordered\_map<int, int \*>::const_iterator 则是访问 unordered_map 需要的数据结构
