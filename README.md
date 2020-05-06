# DataStructureInterface

> data structure and algorithm API with the implementation of C++.

[TOC]

## 1 Issues

### 1.0 General

| id   | description               | finished |
| ---- | ------------------------- | -------- |
| 0    | API doc                   |          |
| 1    | project file arrangement  | √        |
| 2    | test code                 | √        |
| 3    | exception class           | √        |
| 4    | assert func for unit test | √        |
| 5    | unittest template func    | √        |



### 1.1 Data Structure

#### 1.1.1 Vector

|id|description|finished|
|-|-|-|
|1|bug: insert cannot push_back|√|
|2 |finish all api| √ |
|3 |robust with exception process| |
|4 |index with miu number| |
| 5 |lxc namespace| √ |
|6 |bug: operator<<| √ |
| 7 |sort and unsort default para "high"| √ |
| 8 |const static variable and function management| √ |
| 9 |to_str use lxc::String| √ |
| 10 |NOT_FOUND flag|  |



#### 1.1.2 String

|id|description|finished|
|-|-|-|
|1|constructor: not unnamed object warning|√|
|2|cstr_cpy: from source to dest and reuse this method|√|
|3|para high default value: npos|√|
|4|replace --> insert, erase, append? **NO!**|√|
|5|is size redundant? **No!**|√|
|6|types(int, float, ....) convert 2 String||
|7|index: slice operation||
|8|replace, insert at index of size|√|
|9|split|√|
|10|operator>>|√|
|11|compare|√|
|12|exception: input cstr == NULL|√|



#### 1.1.3 List

| id   | description              | finished |
| ---- | ------------------------ | -------- |
| 1    | ListNode operator<< & >> |          |





### 1.2 Algorithm



## 2 Unit Test

### 2.1 Data Structure

#### 2.1.1 Vector

|id|method name|tested|passed|
|-|-|-|-|
|1|constructor|√|√|
|2|resize|√|√|
|3|reserve|√|√|
|4|get|√|√|
|5|front|√|√|
|6|back|√|√|
|7|find|√|√|
|8|search|√|√|
|9||||

#### 2.1.2 String

|id|method name|tested|passed|
|-|-|-|-|
|1|constructor|√|√|
|2|operator=|√|√|
|3|resize|√|√|
|4|reserve|√|√|
|5|clear|√|√|
|6|operator+=|√|√|
|7|append|√|√|
|8|push_back|√|√|
|9|assign|√|√|
|10|insert|√|√|
|11|erase|√|√|
|12|replace|√|√|
|13|copy|√|√|
|14|swap|√|√|
|15|operator<<=>>===!=|√|√|
|16|find|√|√|
|17|rfind|√|√|
|18|find_first_of|√|√|
|19|find_last_of|√|√|
|20|find_first_not_of|√|√|
|21|find_last_not_of|√|√|
|22|substr|√|√|
|23|split|√|√|
|24|compare|√|√|
|25|_shrink|√|√|
|26|_expand|√|√|
|27|_cstr_len|√|√|
|28|_cstr_copy|√|√|
|29|_cstr_comp|√|√|
|30|_cstr_equal|√|√|

#### 2.1.3 List

| id   | method name | tested | passed |
| ---- | ----------- | ------ | ------ |
| 1    | constructor |        |        |



## 3 Reference

1. [MOOC of Deng Junhui](https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/index.htm)
2. C++ STL API
3. CLRS