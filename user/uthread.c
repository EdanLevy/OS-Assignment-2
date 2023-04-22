#include "uthread.h"
#include "user.h"

struct uthread threads[MAX_UTHREADS];
struct uthread *current_thread;
void uthread_sched(struct uthread *current);
/*
initialize the user threads table. This function should be called once.
*/
void init_uthreads()
{
    int i;

    for (i = 0; i < MAX_UTHREADS; i++)
    {
        threads[i].state = FREE;
        threads[i].next_thread = &threads[(i + 1) % MAX_UTHREADS];
    }

    current_thread = threads;
}

int uthread_create(void (*start_func)(), enum sched_priority priority)
{
    static int init_flag = 1;

    if (init_flag == 1)
    {
        init_uthreads();
        init_flag = 0;
    }
    struct uthread *uthread;
    for (uthread = threads; uthread < &threads[MAX_UTHREADS]; uthread++)
    {
        if (uthread->state == FREE)
        {
            uthread->priority = priority;
            uthread->context.ra = (uint64)start_func;
            uthread->context.sp = (uint64)uthread->ustack + STACK_SIZE;
            uthread->state = RUNNABLE;
            return 0;
        }
    }
    return -1;
}

void uthread_yield()
{
    struct uthread *current = uthread_self();
    current->state = RUNNABLE;
    uthread_sched(current);
}

enum sched_priority get_highest_priority()
{
    int i;
    enum sched_priority max_priority = LOW;
    for (i = 0; i < MAX_UTHREADS; i++)
    {
        if (threads[i].state == RUNNABLE && threads[i].priority > max_priority)
        {
            max_priority = threads[i].priority;
        }
    }
    return max_priority;
}

void uthread_sched(struct uthread *current)
{
    struct uthread *next_thread = current->next_thread;
    enum sched_priority max_priority = get_highest_priority();

    while (next_thread->state != RUNNABLE || next_thread->priority != max_priority)
    {
        next_thread = next_thread->next_thread;
    }

    struct context old_context = current->context;
    current_thread = next_thread;
    current_thread->state = RUNNING;
    uswtch(&old_context, &current_thread->context);
}

void uthread_exit()
{
    uthread_self()->state = FREE;

    int i;
    int flag = 0;
    for (i = 0; i < MAX_UTHREADS; i++)
    {
        if (threads[i].state != FREE)
            flag = 1;
    }
    if (flag == 0)
    {
        exit(0);
    }

    uthread_sched(uthread_self());
}

int uthread_start_all()
{
    int i;
    int flag = 0;
    for (i = 0; i < MAX_UTHREADS; i++)
    {
        if (threads[i].state != FREE)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        return -1;
    }
    uthread_sched(current_thread);
    return 0;
}

enum sched_priority uthread_set_priority(enum sched_priority priority)
{
    enum sched_priority old_priority = uthread_self()->priority;
    uthread_self()->priority = priority;
    return old_priority;
}

enum sched_priority uthread_get_priority()
{
    return uthread_self()->priority;
}

struct uthread *uthread_self()
{
    return current_thread;
}
