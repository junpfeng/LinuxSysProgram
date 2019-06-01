其中mmap5_w.c和mmap5_r.c是一对文件，
使用方法及现象：首先运行mmap5_r.c，此时输出的都是初始化的数据；
然后另外开一个终端，打开mmap5_w.c,此时观察mmap5_r.c的输出变成了mmap5_w.c的内部写入

