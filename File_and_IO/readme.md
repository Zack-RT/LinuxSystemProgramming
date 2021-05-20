# 文件与IO（一）

## 什么是IO
- 输入/输出是主存和外部设备之间拷贝数据的过程
  - 设备->内存(输入操作)
  - 内存->设备(输出操作)
- 高级I/0
  - ANSI C提供的标准I/O库称为高级I/O，通常也称为带缓冲的I/O
- 低级I/O
  - 通常也称为不带缓冲的I/O

## 文件描述符

- 对于Linux而言，所有对设备或文件的操作都是通过文件描述符进行的。
- 当打开或者创建一个文件的时候，内核向进程返回一个文件描述符（非负整数）。后续对文件的操作只需通过该文件描述符，内核记录有关这个打开文件的信息。
- 一个进程启动时，默认打开了3个文件，标准输入、标准输出、标准错误，对应文件描述符是0(STDIN_FILENO） 、1 (STDOUT_FILENO） 、2(STDERR_FILENO）,这些常量定义在unistd. h头文件中。
- fileno:将文件指针转换为文件描述符
- fdopen:将文件描述符转换为文件指针

## 文件系统调用

### open(2)
- 有几种方法可以获得允许访问文件的文件描述符。最常用的是使用open ()(打开）系统调用
- 函数原型
  - int open(const char *path, int flags);
- 参数
  - path :文件的名称，可以包含（绝对和相对）路径
  - flags:文件打开模式
- 返回值
  - 打开成功，返回文件描述符;
  - 打开失败，返回—1

### open(3)

- 函数原型
  - int open(const char *path, int flags,mode_t mode);
- 参数
  - path :文件的名称，可以包含（绝对和相对）路径
  - flags:文件打开模式，见下表
  - mode:用来规定对该文件的所有者，文件的用户组及系统中其他用户的访问权限，见下表
- 返回值
  - 打开成功，返回文件描述符;
  - 打开失败，返回-1

打开方式|描述
-|-
O_RDONLY|打开一个供读取的文件
O_WRONLY|打开一个供写入的文件
O_RDwR|打开一个可供读写的文件
O_APPEND|写入的所有数据将被追加到文件的末尾
O_CREAT|打开文件，如果文件不存在则建立文件
O_EXCL|如果已经置O_CREAT且文件存在，则强制open ()失败
O_TRUNC|在open ()时，将文件的内容清空

打开方式|描述
-|-
S_IRUSR|文件所有者的读权限位
S_IwUSR|文件所有者的写权限位
S__IXUSR|文件所有者的执行权限位
S_IRwXU|S_IRUSR\|S_IwUSR\|\S_IXUSR
S_IRGRP|文件用户组的读权限位
S_IwGRP|文件用户组的写权限位
S_IXGRP|文件用户组的执行权限位
S_IRWXG|S_IRGRP\|S_IwGRP\|S_IXGRP
S_IROTH|文件其他用户的读权限位
S_IwOTH|文件其他用户的写权限位
S_IXOTH|文件其他用户的执行权限位
S_IRwXO|SIROTH\|SIwOTH\|S_IXOTH

### close
- 为了重新利用文件描述符,用close()系统调用释放打开的文件描述符
- 函数原型:int close(int fd);
- 函数参数:
  - fd :要关团的文件的文件描述符
- 返回值
  - 如果出现错误，返回-1调用成功返回0

# 文件与IO（二）

### read
- 一旦有了与一个打开文件描述相连的文件描述符，只要该文件是用O_RDONLY或O_RDWR标志打并的，就可以用read()系统调用从该文件中读取字节
- 函数原型:
- ssize_t read(int fd, void *buf, size_t count);
- 参数
  - fd:想要读的文件的文件描述符
  - buf :指向内存块的指针，从文件中读取来的字节放到这个内存块中
  - count :从该文件复制到buf中的字节个数
- 返回值
  - 如果出现错误，返回-1读文件结束,返回0,否则返回从该文件复制到规定的缓冲区中的字节数

### write

- 用write()系统调用将数据写到一个文件中
- 函数原型:
  - ssize_t write(int fd,const void*buf, size_t count);
- 函数参数:
  - fd:要写入的文件的文件描述符
  - buf:指向内存块的指针，从这个内存块中读取数据写入到文件中
  - count:要写入文件的字节个数
- 返回值
  - 如果出现错误，返回-1，如果写入成功，则返回写入到文件中的字节个数

> 读操作一般意味着数据已经从外存读到缓冲区了，但写操作不一定意味着从缓冲区写到外存，除非指定了同步选项 

## 文件的随机读写
- 到目前为止的所有文件访问都是顺序访问。这是因为所有的读和写都从当前文件的偏移位置开始，然后文件偏移值自动地增加到刚好超出读或写结束时的位置，使它为下一次访问作好准备。
- 有个文件偏移这样的机制，在Linux系统中，随机访问就变得很简单，你所需做的只是将当前文件移值改变到有关的位置，它将迫使一次read()或write()发生在这一位置。(除非文件被O_APPEND打开，在这种情况下，任何write调用仍将发生在文件结束处)

### lseek
此函数为linux系统调用，对应c库中的fseek
- 功能说明:通过指定相对于开始位置、当前位置或末尾位置的字节数来重定位curp，这取决于lseek()函数中指定的位置
- 原型:
  - off_t lseek (int fd，off_t offset,int base);
- 参数
  - fd：需设置的文件标识符
  - offset：偏移量
  - base：搜索的起始位置，见下表
- 返回值:返回新的文件偏移值

base|文件位置
-|-
SEEK_SET|从文件开始处计算偏移
SEEK_CUR|从当前文件的偏移值计算偏移
SEEK_END|从文件的结束处计算偏移

## 目录访问

### opendir
- 功能说明:打开一个目录
- 原型:
  - DIR* opendir(char*pathname);
- 参数
  - pathname: 路径名
- 返回值:打开成功，返回一个目录指针打开失败，则返回0

### readdir
- 功能说明:访问指定目录中下一个连接的细节
- 原型:
  - struct dirent* readdir(DIR *dirptr);
- 参数
  - 目录指针
- 返回值:返回一个指向dirent结构的指针，它包含指定目录中下一个连接的细节; 没有更多连接时,返回0
```
struct dirent {
    ino_t          d_ino;       /* Inode number */
    off_t          d_off;       /* Not an offset; see below */
    unsigned short d_reclen;    /* Length of this record */
    unsigned char  d_type;      /* Type of file; not supported
                                  by all filesystem types */
    char           d_name[256]; /* Null-terminated filename */
};
```

### chmode和fchmode
- 功能说明:用来改变给定路径名pathname的文件的权限位

### chown和fchown
- 功能说明:用来改变文件所有者的识别号(ownerid)或者它的用户组识别号(group lD)

# 文件与IO（三）

