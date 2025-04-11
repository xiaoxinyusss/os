//设置当前进程的票数

#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int number = atoi(argv[1]);   //接受一个整数作为命令行参数，并调用atoi函数将其转化为整数型，从而作为票数。
    settickets(number);           //调用settickets（）函数将票数传入内核空间进行操作

    while(1)
    {
        /*因为输入时设置了很多彩票数并需要传入后台运行，因此需要这个循环来等它运行一会。*/
    }

    exit();
}