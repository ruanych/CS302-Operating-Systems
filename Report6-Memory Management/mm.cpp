#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define PROCESS_NAME_LEN 32   //进程名最大长度
#define MIN_SLICE 10          //内碎片最大大小
#define DEFAULT_MEM_SIZE 1024 //总内存大小
#define DEFAULT_MEM_START 0   //内存开始分配时的起始地址

typedef pair<int, string> My_algo;

int mem_size = DEFAULT_MEM_SIZE;
bool flag = 0; //当内存以及被分配了之后，不允许更改总内存大小的flag
static int pid = 0;
My_algo algo[123];
int algo_cnt = 3;
int algo_used = 1;

struct free_block
{ //空闲数据块
    int size;
    int start_addr;
    struct free_block *next;
};

struct allocated_block
{ //已分配的数据块
    int pid;
    int size;
    int start_addr;
    int *data;
    struct allocated_block *next;
};

free_block *free_block_head;                  //空闲数据块首指针
allocated_block *allocated_block_head = NULL; //分配块首指针

void init_algo_info();
allocated_block *find_process(int id);     //寻找pid为id的分配块
free_block *init_free_block(int mem_size); //空闲块初始化
void display_menu();                       //显示选项菜单
void set_mem_size();                       //设置内存大小
void remove_free(free_block *fb, free_block *fb_pre, int size);
int first_fit(int size);
int best_fit(int size);
int worst_fit(int size);
int buddy_system(int size);
int allocate_mem(int size); //为制定块分配内存
void rearrange();           // 对块进行重新分配
int create_new_process();   //创建新的进程
void merge_mem();
int free_mem(allocated_block *ab); //释放分配块
void swap(int *p, int *q);         //交换地址
int dispose(allocated_block *ab);  //释放分配块结构体
void display_mem_usage();          //显示内存情况
void kill_process();               //杀死对应进程并释放其空间与结构体
void Usemy_algo(int id);           //使用对应的分配算法
int pow_ceil(int a);

//主函数
int main()
{
    int op;
    pid = 0;
    init_algo_info();
    free_block_head = init_free_block(mem_size); //初始化一个可以使用的内存块，类似与操作系统可用的总存储空间
    for (;;)
    {
        sleep(1);
        display_menu();
        fflush(stdin);
        if (!scanf("%d", &op))
        {
            printf("Illegal input! Bye~\n");
            return 1;
        }
        //scanf("%d", &op);

        switch (op)
        {
        case 1:
        {
            set_mem_size();
            break;
        }
        case 2:
        {
            if (allocated_block_head != NULL)
            {
                printf("The memory is partially used. The algorithm cannot be set.\n");
            }
            else
            {
                printf("Choose an algorithm\n");
                for (int i = 1; i <= algo_cnt; ++i)
                {
                    printf("%d: %s", algo[i].first, algo[i].second.c_str());
                    if (algo_used == i)
                    {
                        printf(" (current)");
                    }
                    printf("\n");
                }
                printf("Please enter the algorithm serial number, %d~%d: ", 1, algo_cnt);
                int alg;
                scanf("%d", &alg);
                Usemy_algo(alg);
            }
            printf("The current algorithm is %s.", algo[algo_used].second.c_str());
            break;
        }
        case 3:
        {
            create_new_process();
            break;
        }
        case 4:
        {
            kill_process();
            break;
        }
        case 5:
        {
            display_mem_usage();
            break;
        }
        case 233:
        {
            puts("bye....");
            sleep(1);
            return 0;
        }
        defaut:
        {
            break;
        }
        }
    }
}

void init_algo_info()
{
    algo[1] = make_pair(1, "Best Fit");
    algo[2] = make_pair(2, "Worst Fit");
    algo[3] = make_pair(3, "First Fit");
    algo[4] = make_pair(4, "Buddy System");
    algo_cnt = 4;
}

allocated_block *find_process(int id)
{ //循环遍历分配块链表，寻找pid=id的进程所对应的块
    allocated_block *tmp = allocated_block_head;
    while (tmp != NULL)
    {
        if (tmp->pid == id)
        {
            break;
        }
        tmp = tmp->next;
    }
    return tmp;
}

free_block *init_free_block(int mem_size)
{ //初始化空闲块，这里的mem_size表示允许的最大虚拟内存大小
    free_block *p;
    p = (free_block *)malloc(sizeof(free_block));
    if (p == NULL)
    {
        puts("No memory left");
        return NULL;
    }
    p->size = mem_size;
    p->start_addr = DEFAULT_MEM_START;
    p->next = NULL;
    return p;
}

void display_menu()
{
    puts("\n\n******************menu*******************");
    printf("1) Set memory size (default = %d)\n", DEFAULT_MEM_SIZE);
    printf("2) Set memory allocation algorithm\n");
    printf("3) Create a new process\n");
    printf("4) Kill a process\n");
    printf("5) Display memory usage\n");
    printf("233) Exit\n");
    printf("> ");
}

void set_mem_size() //更改最大内存大小
{
    if (flag)
    {
        printf("The memory size has been set and cannot be set again.\n");
    }
    else if (allocated_block_head != NULL)
    {
        printf("The memory is partially used. The memory size cannot be set.\n");
    }
    else
    {
        int size_new = 0;
        printf("Please enter the memory size: ");
        scanf("%d", &size_new);
        if (size_new > 0)
        {
            if (algo_used == 4 && pow_ceil(size_new) != size_new)
            {
                printf("Using algorithm Buddy System requires setting the total memory size to a power of 2.\n");
                return;
            }
            mem_size = size_new;
            free(free_block_head);
            free_block_head = init_free_block(mem_size);
            flag = !flag;
            printf("Successfully set memory size.\n");
        }
        else
        {
            printf("Illegal memory size.\n");
        }
    }
    printf("Current memory size is %d.\n", mem_size);
}

void remove_free(free_block *fb, free_block *fb_pre, int size)
{
    fb->start_addr += size;
    fb->size -= size;
    mem_size -= size;
    if (fb->size == 0)
    {
        if (fb == fb_pre)
        {
            free_block_head = fb->next;
        }
        else
        {
            fb_pre->next = fb->next;
        }
        free(fb);
    }
}

int first_fit(int size)
{
    free_block *tmp = free_block_head;
    free_block *tmp_pre = free_block_head;
    while (tmp != NULL)
    {
        if (tmp->size >= size)
        {
            int start_address = tmp->start_addr;
            remove_free(tmp, tmp_pre, size);
            return start_address;
        }
        tmp_pre = tmp;
        tmp = tmp->next;
    }
    return -1;
}

int best_fit(int size)
{
    free_block *tmp = free_block_head;
    free_block *tmp_pre = free_block_head;
    free_block *best_block = NULL;
    free_block *best_block_pre = NULL;
    int best_size = mem_size + 1;
    while (tmp != NULL)
    {
        if (tmp->size >= size && tmp->size < best_size)
        {
            best_block = tmp;
            best_block_pre = tmp_pre;
            best_size = tmp->size;
        }
        tmp_pre = tmp;
        tmp = tmp->next;
    }

    if (best_block)
    {
        int start_address = best_block->start_addr;
        remove_free(best_block, best_block_pre, size);
        return start_address;
    }
    return -1;
}

int worst_fit(int size)
{
    free_block *tmp = free_block_head;
    free_block *tmp_pre = free_block_head;
    free_block *best_block = NULL;
    free_block *best_block_pre = NULL;
    int best_size = 0;
    while (tmp != NULL)
    {
        if (tmp->size >= size && tmp->size > best_size)
        {
            best_block = tmp;
            best_block_pre = tmp_pre;
            best_size = tmp->size;
        }
        tmp_pre = tmp;
        tmp = tmp->next;
    }

    if (best_block)
    {
        int start_address = best_block->start_addr;
        remove_free(best_block, best_block_pre, size);
        return start_address;
    }
    return -1;
}

int buddy_system(int size)
{
    free_block *tmp = free_block_head;
    free_block *tmp_pre = free_block_head;
    free_block *best_block = NULL;
    free_block *best_block_pre = NULL;
    int best_size = mem_size + 1;
    while (tmp != NULL)
    {
        if (tmp->size >= size && tmp->size < best_size)
        {
            best_block = tmp;
            best_block_pre = tmp_pre;
            best_size = tmp->size;
        }
        tmp_pre = tmp;
        tmp = tmp->next;
    }
    if (best_block)
    {

        while (best_block->size > size)
        {
            int b_size = best_block->size >> 1;
            free_block *p = (free_block *)malloc(sizeof(free_block));
            p->size = b_size;
            p->start_addr = best_block->start_addr + b_size;
            p->next = best_block->next;
            best_block->next = p;
            best_block->size = b_size;
        }
        int start_address = best_block->start_addr;
        remove_free(best_block, best_block_pre, size);
        return start_address;
    }
    return -1;
}

int allocate_mem(int size) //为块分配内存，真正的操作系统会在这里进行置换等操作
{
    if (free_block_head != NULL)
    {
        switch (algo_used)
        {
        case 1:
            return best_fit(size);
        case 2:
            return worst_fit(size);
        case 3:
            return first_fit(size);
        case 4:
            return buddy_system(size);
        default:
            break;
        }
    }
    return -1;
}

int create_new_process()
{ //创建新进程
    int mem_sz = 0;
    printf("Please enter the memory size requested by the new process: ");
    scanf("%d", &mem_sz);
    // Write your code here
    if (mem_sz <= 0)
    {
        printf("Illegal memory size.\n");
    }
    else if (mem_sz <= mem_size)
    {
        if (algo_used == 4)
        {
            mem_sz = pow_ceil(mem_sz);
        }
        int addr = allocate_mem(mem_sz);
        if (addr != -1)
        {
            allocated_block *p;
            p = (allocated_block *)malloc(sizeof(allocated_block));
            if (p == NULL)
            {
                puts("No memory left");
                return -1;
            }
            p->pid = ++pid;
            p->size = mem_sz;
            p->start_addr = addr;
            p->next = NULL;
            if (allocated_block_head == NULL)
            {
                allocated_block_head = p;
            }
            else
            {
                allocated_block *tmp = allocated_block_head;
                while (tmp->next != NULL)
                {
                    tmp = tmp->next;
                }
                tmp->next = p;
            }
            printf("Process created successfully, PID: %d, memory size: %d.\n", p->pid, p->size);
            return 0;
        }
    }
    printf("There is not enough memory to create the process.\n");
    return -1;
}

void swap(int *p, int *q)
{
    int tmp = *p;
    *p = *q;
    *q = tmp;
    return;
}

void rearrange()
{ //将块按照地址大小进行排序
    free_block *tmp, *tmpx;
    puts("Rearrange begins...");
    puts("Rearrange by address...");
    tmp = free_block_head;
    while (tmp != NULL)
    {
        tmpx = tmp->next;
        while (tmpx != NULL)
        {
            if (tmpx->start_addr < tmp->start_addr)
            {
                swap(&tmp->start_addr, &tmpx->start_addr);
                swap(&tmp->size, &tmpx->size);
            }
            tmpx = tmpx->next;
        }
        tmp = tmp->next;
    }
    usleep(500);
    puts("Rearrange Done.");
}

void merge_mem()
{
    free_block *tmp = free_block_head;
    bool cond = algo_used != 4;
    while (tmp != NULL && tmp->next != NULL)
    {
        free_block *next = tmp->next;
        if (tmp->start_addr + tmp->size == next->start_addr && (cond || tmp->size == next->size))
        {
            tmp->size += next->size;
            tmp->next = next->next;
            free(next);
            if (algo_used == 4)
            {
                tmp = free_block_head;
            }
        }
        else
        {
            tmp = tmp->next;
        }
    }
}

int free_mem(allocated_block *ab)
{
    free_block *p = (free_block *)malloc(sizeof(free_block));
    p->size = ab->size;
    p->start_addr = ab->start_addr;
    p->next = free_block_head;
    free_block_head = p;
    mem_size += ab->size;
    rearrange();
    merge_mem();
    return 0;
}

int dispose(allocated_block *fab)
{ //释放结构体所占的内存
    allocated_block *pre, *ab;
    if (fab == allocated_block_head)
    {
        allocated_block_head = allocated_block_head->next;
        free(fab);
        return 1;
    }
    pre = allocated_block_head;
    ab = allocated_block_head->next;
    while (ab != fab)
    {
        pre = ab;
        ab = ab->next;
    }
    pre->next = ab->next;
    free(ab);
    return 2;
}

void display_mem_usage()
{
    free_block *fb = free_block_head;
    allocated_block *ab = allocated_block_head;
    puts("*********************Free Memory*********************");
    printf("%20s %20s\n", "start_addr", "size");
    int cnt = 0;
    while (fb != NULL)
    {
        cnt++;
        printf("%20d %20d\n", fb->start_addr, fb->size);
        fb = fb->next;
    }
    if (!cnt)
        puts("No Free Memory");
    else
        printf("Totaly %d free blocks\n", cnt);
    puts("");
    puts("*******************Used Memory*********************");
    printf("%10s %10s %20s\n", "PID", "start_addr", "size");
    cnt = 0;
    while (ab != NULL)
    {
        cnt++;
        printf("%10d %10d %20d\n", ab->pid, ab->start_addr, ab->size);
        ab = ab->next;
    }
    if (!cnt)
        puts("No allocated block");
    else
        printf("Totaly %d allocated blocks\n", cnt);
    return;
}

void kill_process()
{ //杀死某个进程
    allocated_block *ab;
    int pid;
    printf("Please input the pid of Killed process: ");
    scanf("%d", &pid);
    ab = find_process(pid);
    if (ab != NULL)
    {
        free_mem(ab);
        dispose(ab);
        printf("Successfully killed the process, process id: %d.\n", pid);
    }
    else
    {
        printf("The process does not exist.\n");
    }
}

void Usemy_algo(int id)
{
    if (id >= 1 && id <= algo_cnt)
    {
        if (id == 4)
        {
            if (pow_ceil(mem_size) != mem_size)
            {
                printf("Using algorithm Buddy System requires setting the total memory size to a power of 2.\n");
                return;
            }
        }
        algo_used = id;
        printf("The setting is successful.\n");
    }
    else
    {
        printf("Illegal algorithm serial number.\n");
    }
}

int pow_ceil(int a)
{
    int check = 1;
    while (check < a)
    {
        check = check << 1;
    }
    return check;
}
