# Report4



## Q1

Describe Function(功能) of  **pthread\_create**:

>pthread\_create 函数的功能是：在调用该函数的进程中创建一个新线程。
>
>传递给函数的参数分别是 pthread\_t \*thread 指向线程标识符的指针；const pthread_attr_t \*attr 设置线程属性； void \*(start_routine) (void \*) 线程运行函数的起始地址； void \*arg 运行函数的参数。 新线程通过调用start\_routine() 开始执行；arg作为start\_routine（）的唯一参数传递。
>
>pthread\_create的返回值:若成功，返回0；若出错，返回出错编号。



## Q2

 Describe Function(功能) of **pthread\_join**:

>   pthread\_join 函数的功能是以阻塞的方式等待指定线程的结束，可用于线程间同步的操作，一般是主线程对所有创建的线程使用该函数。
>
>   当函数返回时，被等待线程的资源被收回。 如果线程已经结束，那么该函数会立即返回。
>
>   传递给函数的参数分别是 pthread\_t thread 线程标识符，即线程ID，标识唯一线程； void \*\*retval，用户定义的指针，用来存储被等待线程的返回值。
>
>   pthread\_join 的返回值 ： 0代表成功。 失败，返回的则是错误号。



## Q3

Describe Function(功能) of **pthread\_mutex\_lock**:

>   pthread\_mutex\_lock 函数的功能是 锁住传入的互斥锁。当pthread\_mutex\_lock()返回时，该互斥锁已被锁定。线程调用该函数让互斥锁上锁，如果该互斥锁已被另一个线程锁定和拥有，则调用该线程将阻塞，直到该互斥锁变为可用为止。
>
>   pthread\_mutex\_lock 和 pthread\_mutex\_unlock 配套使用。两句函数中间的代码就是被上锁的代码，被上锁的代码只能有一个线程使用，别的线程执行到这里会发生阻塞，只有unlock之后，别的线程才能使用lock之后进入代码。
>
>   pthread\_mutex\_lock 的参数是 pthread\_mutex\_t \*mutex。
>
>   pthread\_mutex\_lock 的返回值：在成功完成之后会返回零。其他任何返回值都表示出现了错误。



## Q4

Describe Function(功能) of **pthread\_cond\_wait**

>   pthread\_cond\_wait 函数的功能是 阻塞当前线程直到收到其他线程发送的特定信号才被唤醒。
>
>   条件变量是的一种机制，主要包括两个动作：一个线程等待"条件变量的条件成立"而挂起；另一个线程使"条件成立"（给出条件成立信号）唤醒被挂起的该线程。为了防止竞争，条件变量的使用总是和一个互斥锁结合在一起。



## Q5

Describe Function(功能) of **pthread\_cond\_signal**:

>   假如有多个线程正在阻塞等待着这个条件变量的话，那么是根据各等待线程优先级的高低确定哪个线程接收到信号开始继续执行。如果各线程优先级相同，则根据等待时间的长短来确定哪个线程获得信号。但无论如何一个pthread\_cond\_signal调用最多发信一次。
>
>   如果有多个被阻塞的线程等待此条件变量，则根据每个线程的优先级确定哪个线程接收到该信号。如果每个线程的优先级相同，则根据等待时间确定哪个线程收到该信号。但是无论如何，一个 pthread\_cond\_signal 信号调用最多只能发送一次消息。



## Q6

Describe Function(功能) of **pthread\_mutex\_unlock**:

>   pthread\_mutex\_unlock 的功能是解除锁定 mutex 所指向的互斥锁。传入的参数是 pthread\_mutex\_t \*mutex， 结果是将传入的该互斥锁解除锁定状态。



## Q7

Describe Function(功能) of **sem\_open**:

>   sem\_open 函数的功能是创建并初始化有名信号量或打开一个已存在的有名信号量。
>
>   传递给函数的参数是 const char \*name 信号量的名字（标识符）； int oflag 控制调用操作的标志；mode\_t mode 权限位； unsigned int value 信号量初始值。
>
>   sem\_open 的返回值：成功时返回指向信号量的指针，出错时为SEM\_FAILED。



## Q8

 Describe Function(功能) of **sem\_wait**:

>   sem\_wait 函数的功能是减小(锁定)由sem指定的信号量的值。如果信号量的值比0大，那么进行减一的操作，函数立即返回。如果信号量当前为0值，则调用阻塞，直到信号量变得可以进行减一的操作(上升到零以上)，或者是信号处理程序中断调用。
>
>   传递的参数是 sem\_t \*sem 需要进行减一操作的信号量。
>
>   sem\_wait 的返回值：成功返回0，错误的话信号量的值不改动，返回-1，errno设定来标识错误。



## Q9

Describe Function(功能) of **sem\_post**:

>   sem\_post 函数的功能是增大(解锁)由sem指定的信号量的值。如果信号量的值大于0，则在 sem\_wait 函数调用中阻塞的另一个进程或线程将被唤醒并继续锁定信号量。它是一个“原子操作”，即同时对同一个信号量做加“1”操作的两个线程是不会冲突的。传递的参数是 sem\_t \*sem 需要进行加一操作的信号量。sem\_post 的返回值： 成功时返回 0；错误时，信号量的值没有更改，返回 -1，并设置 errno 来指明错误。



## Q10

Describe Function(功能) of **sem\_close**:

>   sem\_close 函数的功能是 关闭 sem 引用的指定信号量，允许释放系统已分配给调用过程的任何资源，以释放此信号量。传递的参数是 sem\_t \*sem 需要释放的信号量。sem\_close 的返回值：成功时返回0；出错时返回-1，并设置errno以指示错误。



## Q11

Producer-Consumer Problem（understand producer_consumer.c）: Are the data that consumers read from the buffer are produced by the same producer? [producer_consumer.c](./producer_consumer.c)

>   在本题提供的 producer\_consumer.c 中，消费者和生产者均只有一个，消费者从缓冲区读取的数据由同一生产者产生。
>
>   对于生产者消费者问题，如果存在多个生产者，则消费者从缓冲区读取的数据不一定由同一生产者产生。



## Q12

Producer-Consumer Problem（understand producer\_consumer.c）: What is the order of the consumer's read operations and the producer's write operations, and their relationship

>   顺序：消费者的读取操作在生产者的写入操作之后。
>
>   关系：一开始的时候缓冲区是空的，生产者可以写入数据，而只有生产者写入数据到缓冲区，消费者才有可能从缓冲区中读取数据，所以是有了生产者的成功写入操作才会有消费者的成功读取，生产者写入操作在前，消费者的读取操作在后。



## Q13

Producer-Consumer Problem（understand producer_consumer.c）: Briefly describe the result of the program

>   程序创建两个线程分别用于生产者生产数据和消费者消费数据。
>
>   生产者和消费者均通过互斥锁保护缓冲区 (buffer) 避免被同时操作(写入或者读出)。
>
>   程序通过以下方式保证了生产者消费者读写数据的安全(不会丢失数据以及消费者一直等但是等不到数据)：
>   当生产者获得 buffer 互斥锁想要写入数据但是缓冲区满时，生产者会使用 pthread\_cond\_wait 和条件变量 full 休眠并释放互斥锁，等待消费者消费数据前(已获得互斥锁)唤醒生产者。
>   当消费者获得 buffer 互斥锁想要读出数据但是缓冲区空时，消费者会使用 pthread\_cond\_wait 和条件变量 empty 休眠并释放互斥锁，等待生产者生产数据前(已获得互斥锁)唤醒消费者。
>
>   生产者每次随机产生一个大写英文字母放到缓冲区中，缓冲区的内容、生产者生产的内容、消费者消费的内容均通过 drawing 函数 格式化输出到控制台。



## Q14

Producer-Consumer Problem（understand producer\_consumer.c）: What queue is used in this program, and its characteristics?

>   本程序使用的是环形队列，特点是其使用定长数组实现，数组首尾相连，数据先进先出，可以通过记录入队出队下标确定队列是否已满或者为空，操作速度也比较快。



## Q15

Producer-Consumer Problem（understand producer\_consumer.c）: Briefly describe the mutual exclusion mechanism of this program

>   在本程序中，对 buffer 进行操作（读或写数据）之前需要得到互斥锁，操作结束之后或者遇到特殊情况时释放互斥锁。
>
>   特殊情况指的是 
>
>   1.  生产者得到互斥锁时发现 buffer 满了无法写入数据，此时生产者释放互斥锁以及使用 pthread\_cond\_wait 和条件变量 full 休眠，之后消费者可以拿到互斥锁然后消费数据唤醒生产者
>
>   2.  消费者得到互斥锁发现 buffer 为空无法读出数据，此时消费者释放互斥锁以及使用 pthread\_cond\_wait 和条件变量 empty 休眠，之后生产者可以拿到互斥锁然后生产数据唤醒消费者
>
>   这样的机制保证 buffer 不能被同时读写数据，buffer 为空时不会被误读数据，buffer 为满时不会丢失数据。

