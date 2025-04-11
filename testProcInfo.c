//显示当前正在运行的进程的信息,包括进程ID、是否可运行、分配的彩票数和已累积的CPU时间片数（ticks)

#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

int main(int argc, char *argv[])
{
    int count = 0;       //记录一共调用多少时间片
    struct pstat ps;
    getpinfo(&ps);       //通过调用 getpinfo() 系统调用来获取进程信息

    //将其打印到标准输出(printf参数1是输出流，表示输出到哪里)
    printf(1, "\n------------ Initially assigned Tickets = %d ----------\n", InitialTickets);
    printf(1, "\nProcessID\tRunnable(0/1)\tTickets\t\tTicks\n");
    for(int i = 0; i < NPROC; i++)               //NPROC是最大进程数
    {
        if(ps.pid[i] && ps.ticket[i] > 0)        //判断该进程是否存在，同时彩票值是否大于0
        {
            printf(1, "%d\t\t%d\t\t%d\t\t%d\n", ps.pid[i], ps.inuse[i], ps.ticket[i], ps.tick[i]);
            count += ps.tick[i];
        }
    }
    printf(1, "\n------------------- Total Ticks = %d -----------------\n\n", count);
    exit();
}