#include "types.h"
#include "pstat.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_settickets(void)
{
  int number;
  argint(0, &number);    //通过argint函数从用户空间获取参数放入number中（相当于寄存器） 
  if(number < 0)
  {
    return -1;           //如果票数小于0,是不合规的
  }
  else if(number == 0)
  {
    return settickets(InitialTickets);     //如果票数等于0，相当于没有设置任何彩票，需要保持初始状态
  }
  else
  {
    return settickets(number);     //进行进程里的彩票调用
  }
}

int sys_getpinfo(void)
{
  struct pstat *ps;
  if(argptr(0, (char **)&ps, sizeof(struct pstat)) < 0)   //把寄存器里的内容传到ps指针
  {
    return -1;
  }
  getpinfo(ps);           //把ps指针传给掌管进程的函数
  return 0;
}