# Submit


| Content    | File | Grades | Remarks |
| ---------- | ------ | ------ | ------ |
| Report | [Report3.md](./Report3.md) | 80/80  |   |
| Code | [11812109_RYC_scheduler.c](./11812109_RYC_scheduler.c) | 20/20  |   |

<br>

# Scheduler Task

Modify: do_stat() in scheduler.c such that it can also output jobname, current priority and default priority
Implement schedule strategy:

Job with highest priority runs first. If same priority is shared, the job that has waited longest runs first.

Priority add 1 after waiting for 100ms

Priority reset to initial priority after running.

请将修改后的scheduler.c的代码提交，命名为“学号_姓名_scheduler.c”