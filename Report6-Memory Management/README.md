# Submit


| Content    | File | Grades | Remarks |
| ---------- | ------ | ------ | ------ |
| Report | [Report6.md](./Report6.md) | 50/50  |   |
| Code | [mm.cpp](./mm.cpp) | 60/60 |   |

<br>


# Memory Management Task

## Guide

### Basic requirements of code (50+10 points) 

Understand the given code and complete it. So that it can achieve basic memory
management goals: 

+ allocate a given memory space to a process (15 points)
+ kill a process and release the memory space the process kept(15 points)
+ show the memory usage (5 points)
+ realize three kinds of algorithms--First fit、Best fit、worst fit (15 points)
+ realize Buddy system (bonus, 10 points) 


### Report (50 points) 


### Things help you to do this lab: 

+ How to make your vim powerful? 
  - Auto complement: https://www.linuxidc.com/Linux/2017-02/141088.htm
  - Supporting Chinese character: https://www.zhihu.com/question/22363620
  - Write more code 

+ More explanation about code:
  - My idea: Keep a list of free-block, which stores memory blocks we can use. And also
    keep a list of allocated-block, which stores memory blocks we have allocated. When
    we allocated a memory block to a process, we also need to store the pid of this
    process. So when we want to kill process, we can find the correct block. 
  - Two import functions you need to complete: 
    + `int allocate_mem(allocated_block *ab)` which give a block memory space 
    + `int free_mem(allocated_block *ab)` which release the memory space for this block
    <br><br> For allocate, you should use your own algorithm to allocate memory space. That means you need to do something on the *free-block list*
    <br>For free, when we free the memory space, we need to add the block to the *free-block list*. At this time, you also need to change the list by your own algorithm. 
  - Some other things:
    + *typedef pair<int, string> My\_algo*; This line define my own type called My_algo. You can declare a variable of this type. The first component is an integer, the second component is a string. That means:
      <br> &nbsp;&nbsp;&nbsp; My_algo algo; 
      <br> &nbsp;&nbsp;&nbsp; algo = make_pair(0, “FirstFit”); 
      <br> &nbsp;&nbsp;&nbsp; printf(“%d %s\n”, algo.first, algo.second);
      <br> &nbsp;&nbsp;&nbsp; After running this code, you will get result: 0 FirstFit
      <br> make\_pair is a function, which you don’t need to write by your own.
    + NULL. When you deal with pointers, please pay attention to NULL. That is, only when a pointer is not NULL, it can has next element.   

<br>

### Some Test cases:

+ (1, 2048), 2, 1, 5, (3, 1024), 3(1023), 5, (4, 1), 5, (4, 2), 233
+ (3, 1024), 5, (3, 1), (4, 1), 5, (4, 2), 233
+ (1, 700), 2, 2, (3, 100), (3, 200), (3, 300), (4, 2), 5, (3, 300), 5, (4, 3), 5, 233

## Additional explanation for code [mm.cpp](./mm_old.cpp) of report6

1. Menu option 1 will not be executed more than once
2. Test cases would specify an algorithm before allocating space to the process
3. Buddy system only allocate space of 2^k units, in which k is an integer
4. If there has no enough space for a new process, the process will not execute.
5. After killing a process, continuous free space needs to be merged

Here is an example for case 5:

**after (2,1),(3,200),(3,300),(3,300),(3,200),5 you should get:**

```
******Free Memory******
   start_addr size
       1000   24
Totaly 1 free blocks
*******Used Memory*********
 PID ProcessName start_addr size
  1   process1    0        200
  2   process2    200      300
  3   process3    500      300
  4   process4    800      200
Totaly 4 allocated blocks
```

**Then,after (4,1),(4,2),(4,4),5 you should get:**

```
******Free Memory******
   start_addr size
      0       500
      800     224
Totaly 2 free blocks
*******Used Memory*********
 PID ProcessName start_addr size
  3   process3     500      300
Totaly 1 allocated blocks
```

**Then,after (3,100),5 you should get:**

```
******Free Memory******
   start_addr size
      0       500
     900      124
Totaly 2 free blocks
*******Used Memory*********
 PID ProcessName start_addr size
  3   process3      500     300
  5   process5      800     100
Totaly 2 allocated blocks
```

