# Submit


| Content    | File | Grades | Remarks |
| ---------- | ------ | ------ | ------ |
| Report | [Report1.md](./Report1.md) | 40/40  |   |
| Code | [11812109.sh](./11812109.sh) | 60/60  |   |

<br>

# Shell Script Task

## Test Guide

1. unzip the *[test_case.zip](test_case.zip)* file, the structure of *test_case.zip* is:
```text
test_case.zip
├── baseline.sh    // the test script
├── answer.file    // the standard answer supplied
└── test_directory // the test directory
```

2. `cd test_case` (make sure your test is under this directory)

3. run `./baseline.sh ./yourscript.sh`

4. The script will generate two new files after step3 (*result.file* and *output.file*).
   Don’t worry, the script will tell you if you are right.
   If not right, then you need to check the *result.file* and *output.file*.

<br>

## About Shell Script

<u>Test format</u>: ./lab1-xxxx.sh parameter1 parameter2

1. *parameter1* is the target directory, which could be an **absolute path** or a **relative path**. It may
   contain special characters, such as blank, "$", "*", etc.
   
2. *parameter2* is the output file path, which could be an **absolute path** or a **relative path**. The
   file path may not exist, you need to create it in this case. And also the file path may contain
   special characters too. You should write your results to this file, because we need use script to
   compare your result with the standard answer.

<br>

<u>Result format</u>:
1. all the paths must be absolute.

2. use one blank line to separate the two information block. If a directory is empty, you also
   should list its name by \[name\].

3. file/directory should be listed in dictionary order.

<u>Notice</u>:
1. The hidden file/directory is not in the scope our test cases, so you needn’t process it.
2. The link file/directory is not in the scope our test cases, so you needn’t process it.


## About Report:
1. For–o0 –o1 problem, you need to analysis the assembly code and explain the difference of two
   optimization level, instead of just pasting your screenshot.
2. Conclusion part want you conclude the knowledge/experience when you finish lab1 homework,
   it depend on yourself. This part doesn't count, but this is a good way to sum up and improve yourself.


## Appendix:
<u>Possible Path Format</u>:

| absolute path                | absolute path             |
| ---------------------------- | ------------------------- |
| **/home/student1/test\_dir** | test\_dir                 |
|                              | ../test\_dir              |
|                              | ../../test_path/test\_dir |
|                              | ./                        |
|                              | test_dir                  |

