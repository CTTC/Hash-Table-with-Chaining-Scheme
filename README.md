# Hash-Table-with-Chaining-Scheme
The code file build a hash table using chaining scheme. It also contains some methods in order to test the hash table. To test the hash table, the table was used to store strings and quickly find strings. The code file contains two methods to cope with the input command. One is a naive algorithm and the other one is an efficient algorithm with a hash table using list chaining.

####The input format is :

A single integer m in the first line, which is the number of buckets. 

The next line contains the number of queries N. 

It’s followed by N lines, each of them contains one query in the format of "add (string)", "del (string)", "find (string)", "check (i)".

####The output format is:
Print the result of each of the find and check queries, one result per line, in the same order as these queries are given in the input.

####Example:
#####Input:
```
5
12
add world
add HellO
check 4
find World
find world
del world
check 4
del HellO
add luck
add GooD
check 2
del good
```

#####Output:
```
HellO world
no
yes
HellO
GooD luck
```
