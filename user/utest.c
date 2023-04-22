#include "uthread.h"
#include "user.h"

void fun1()
{
    printf("fun1\n");
    uthread_exit();
}

void fun2()
{
    printf("fun2\n");
    uthread_exit();
}

void fun3()
{
    for (int i = 0; i < 50; i++)
    {
        printf("fun3,%d\n",i);
        uthread_yield();
    }
    uthread_exit();
}
void fun4()
{
    printf("++++++++++++++++++++++\n");
    uthread_exit();
}

int main()
{
    int i;
    for (i = 0; i < 50; i++)
    {
        uthread_create(fun4, LOW);
        uthread_create(fun3, LOW);
        uthread_create(fun1, HIGH);
        uthread_create(fun2, MEDIUM);
        uthread_start_all();
    }
    exit(0);
}