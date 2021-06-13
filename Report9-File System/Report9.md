# Report9



## Q1

Consider a really simple filesystem, **cs302fs**, where each inode only has 10 direct pointers, each of which can point to a single file block. Direct pointers are 32 bits in size (4 bytes). What is the maximum file size for **cs302fs**?( Assume, for all of the questions in this part, that filesystem blocks are 4 KBytes. )

>   10*4 KB = 40 KB



## Q2

Consider a filesystem, called **extcs302fs**, with a construct called an extent. Extents have a pointer (base address) and a length (in blocks). Assume the length field is 8 bits (1 byte). Assuming that an inode has exactly one extent. What is the maximum file size for **extcs302fs**? ( Assume, for all of the questions in this part, that filesystem blocks are 4 KBytes. )

>   ( 2^8 - 1 ) * 4 KB = 1020 KB



## Q3

Consider a filesystem that uses direct pointers, but also adds indirect pointers and double-indirect pointers. We call this filesystem, **indcs302fs**. Specifically, an inode within **indcs302fs** has 1 direct pointer, l indirect pointer, and 1 doubly-indirect pointer field. Pointers, as before, are 4 bytes (32 bits) in size. What is the maximum file size for **indcs302fs**?  ( Assume, for all of the questions in this part, that filesystem blocks are 4 KBytes. )

>   1 * 4 KB + 1 * ( 4 KB / 4 B ) * 4 KB + 1 * ( 4 KB / 4 B ) * ( 4 KB / 4 B ) * 4 KB = 1049601 KB = 4 KB + 4 MB + 4 GB



