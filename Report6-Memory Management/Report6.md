# Report6



## Q1

What is Uniprogramming:

What is the shortcoming of Uniprogramming:

>   1.  Uniprogramming 是指在物理内存中，除了 OS 之外，一个时间内至多存在一个应用程序，也就是说同一时间只能运行一个程序，该程序可以访问任何物理地址，没有地址转换。
>
>   2.  Uniprogramming 的缺点是效率低，功能性弱，如果正在运行的程序进行 IO 操作会浪费CPU时间，并且没有用户实时互动（同一时间只有一个程序在运行）。




## Q2

What is Multiprogramming:

What is the shortcoming of Multiprogramming:

>   1.  Multiprogramming 是指在物理内存中，除了 OS 之外，一个时间内可以同时存在多个应用程序。
>   2.  Multiprogramming 的缺点是更复杂，其必须以某种方式防止程序之间物理内存中的地址重叠，需要管理物理内存的分配（尽可能高效地利用物理内存，这种管理也是需要消耗资源的）。



## Q3

 What is the segmentation mechanism and its advantages & disadvantages:

>   1. 分段机制将内存分成若干个长度不等的段，每个段都有名称和长度。地址指定了段名称和段内偏移。分段机制将每一段的虚拟地址空间映射到物理地址空间。比如一个C编译器可能会创建如下段:代码、全局变量、堆、每个线程使用的栈、标准的C库。
>
>   2.  优点:使数据更加“逻辑化”，易于共享；便于实现“保护”机制；减少碎片（相对于分配连续固定大小内存空间给一个进程）。
>
>   3.  缺点: 段大小不是固定的，比较复杂；一个进程需要多次分配内存；碎片较小，但仍然是一个问题。



## Q4

 What is the paging mechanism and its advantages & disadvantages:

>   1.  分页机制将物理内存分为固定大小的块(称为帧，frame)，而将逻辑内存也分为同样大小的块（称为页，page），可将用户程序的任一页放在内存的任一块中，并维护一个页表保存虚拟地址和物理地址之间的关系。
>
>   2.  优点：易于实现；减少外部碎片，避免紧缩；避免了将不同大小的内存块匹配到交换空间的麻烦问题。
>
>   3.  缺点：需要额外的空间资源保存页表；无法避免内碎片。



## Q5

How to reduce the occurrence of internal fragmentation when allocating memory? Briefly explain why this method works.

>   可以使用动态内存分配（First fit、Best fit、Worst fit）方式减少内碎片。
>
>   动态内存分配可以最大地减少内碎片，分页方式(最后一页)、buddy system 可能会产生较大的内碎片，而动态内存分配在最小分配单元是 byte 的时候产生的单个内碎片最大是 7 bit。



## Q6

How to reduce the occurrence of external fragmentation when allocating memory? Briefly explain why this method works.

>   可以使用紧缩（condensation）和分页方式减少外碎片的产生。
>
>   紧缩（condensation）通过整理空闲内存到一个大的块中，使得多个外碎片变成一个大块以至于这个大块不再是外碎片。
>
>   分页方式固定了页面的大小，如果页面空闲那么一定会可以被分配出去，于是不存在外碎片（但是可能会产生将近一页的内碎片）。

