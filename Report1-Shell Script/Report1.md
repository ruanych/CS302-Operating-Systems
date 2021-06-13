# Report1



## Description:

Task 1.Run commands: ls, cd, man, mkdir, rm, mv, cp, cat, grep, ps, kill

Task 2. Compile the program in Tutorial 0 (as shown in screenshot). Check the assembly language under O0 and O1 standards

Task 3.Finish the shell script task in Lab1 (Tutorial_1_shell task）



## Q1

run " **mkdir ~/studentID** " （replacing studentID with your own ID）

Answer the function and parameter meaning:

>   功能：如果指定目录不存在则创建该目录。
>
>   参数含义：
>
>       ~/studentID  想要创建的目录



## Q2

run " **ls –la ~** " 

Answer the function and parameter meaning:

>   功能：列出目录内容
>
>   参数含义：
>
>      -a  不要忽略以开头的条目
>
>      -l   以长格式的形式查看当前目录下所有可见文件的详细属性
>
>      ~ 需要查看的目录



## Q3

run " **cd ~/studentID** "  (replacing studentID with your own ID) 

Answer the function and parameter meaning:

>   功能：进入一个目录
>
>   参数含义：
>
>      ~/studentID  希望进入的目录



## Q4

run " **man grep** "

Answer the function and parameter meaning:

>   功能：系统参考手册的接口
>
>   参数含义：
>
>      grep： 希望在手册中查阅的命令



## Q5

run " **mv ~/studentID /home** " and " **ls /home** "  (replacing studentID with your own ID) 

Answer the function and parameter meaning:

>   mv指令
>
>   功能：移动（或重命名）文件（或目录）
>
>   参数含义：
>
>   ​    ~/StudentID 源目录
>
>   ​    /home 目的目录
>
>   
>
>   ls 指令
>
>   功能：列出目录内容
>
>   参数含义：
>
>      /home 需要查看的目录



## Q6

run " **rm -r /home/studentID**  "（replacing studentID with your own ID）

Answer the function and parameter meaning: 

>   功能：删除目录或者文件
>
>   参数含义：
>
>      -r 递归删除目录及其内容
>
>      /home/studentID 希望删除的目录



## Q7

run " **cp /etc/apt/sources.list /etc/apt/sources.list.bak** " (replacing studentID with your own ID)

Answer the function and parameter meaning: 

>   功能：复制文件或者目录
>
>   参数含义：
>
>      /etc/apt/sources.list  源文件路径
>
>      /etc/apt/sources.list.bak 目标文件路径



## Q8

run " **cat /etc/shells** " (replacing studentID with your own ID)

Answer the function and parameter meaning:

>   功能：将文件连接到标准输出，即输出文件内容到控制台
>
>   参数含义：
>
>      /etc/shells 目标文件



## Q9

run " **cat /etc/shells | grep bash** " (replacing studentID with your own ID)

Answer the function and parameter meaning:

>   cat 指令同 问题8
>
>      | 把前一条指令的输出作为下一条指令的输入
>
>   
>
>   grep指令
>
>   功能：在每个文件中搜索指定的PATTERNS。PATTERNS是由换行符分隔的一个或多个模式，打印与模式匹配的每一行
>
>   参数含义：
>
>      bash 需要匹配的PATTERNS



## Q10

Open two terminals, find their PIDs by **ps** and kill one of them

Answer the function and parameter meaning: 

>   我使用了 ps a 指令 和 kill PID 指令
>
>   
>
>   ps指令
>
>   功能：报告当前系统的进程状态
>
>   参数含义：
>
>      a 显示现行终端机下的所有程序，包括其他用户的程序
>
>   
>
>   kill指令
>
>   功能：结束一个进程
>
>   参数含义：
>
>      PID 需要结束的进程的ID



## Q11

 Compile and Execute: write following **opt.c** and check the assembly language under **–o0 –o1**

```c
#include <stdio.h>
int main(){
    int x = 0;
    x += 1;
    x += 1;
    x += 1;
    printf("%d\n", x);
    return 0;
}
```

**Answer**

**1）the source code:**

**2）command：**

**3）result：**

**4）difference:**



>   **1）the source code:**
>
>```c
>   #include <stdio.h>
>   int main(){
>       int x = 0;
>       x += 1;
>       x += 1;
>       x += 1;
>       printf("%d\n", x);
>       return 0;
>   }
>```
>    
>
>   **2）command：**
>
>   vim opt.c
>
>   然后输入代码，按Esc键，:，输入 wq，然后按 Enter键
>
>    
>
>   gcc -S opt.c -O0 -o opt0.s
>
>   gcc -S opt.c -O1 -o opt1.s
>
>    
>
>   diff opt0.s opt1.s
>
>   cat opt0.s
>
>   cat opt1.s
>
>    
>
>   **3）result：**
>
>   输出两个不同的编译之后的文件（见截图）
>
>    
>
>   **4）difference:**
>
>   编译后生成的汇编程序，-O1 参数对原代码进行了优化，将三个 += 1 操作变成了 一个 +=3 的操作





## Q12

 Insert your screenshots of Question 1 to 11 into one pdf,and submit the pdf.

>   [Report1_Screenshots](./Report1_Screenshots.pdf)

