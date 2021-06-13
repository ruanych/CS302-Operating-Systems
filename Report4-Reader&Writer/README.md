# Submit


| Content    | File | Grades | Remarks |
| ---------- | ------ | ------ | ------ |
| Report | [Report4.md](./Report4.md) | 50/50  |   |
| Code | [read.h](./read.h), [write.h](./write.h) | 50/50 |   |

<br>

# Reader&Writer Task

Please complete and submit "read.h" and "write.h" (in [reader-writer.zip](./reader-writer.zip)), and You should implement according to the output format in "output_sample.txt“

The conditions that must be satisfied are as follows:


+ Any number of readers can simultaneously read the file

+ Only one writer at a time may write to the file

+ If a writer is writing to the file, no reader can read it

+ When new reader coming,
  - If no reader and writer, then new reader can read.
  - If writer is waiting and other readers are reading, then new reader can read.
  - If writer is writing, then new reader waits.

+ When new writer coming, 
  - If no reader, then new writer can write.
  - If reader is reading, then new writer waits.
  - If writer is writing, then new writer waits.