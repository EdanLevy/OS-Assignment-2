#include "uthread.h"

struct uthread threads[MAX_UTHREADS];
struct uthread *current_thread;

/*
This function receives as arguments a pointer to the user thread’s start
function and a priority. The function should initialize the user thread in a
free entry in the table, but not run it just yet. Once the thread’s fields are
all initialized, the user thread’s state is set to runnable. The function
returns 0 on success or -1 in case of a failure.
Note: do not forget to set the ‘ra’ register to the start_func and ‘sp’ to the
top of the relevant ustack
*/
int uthread_create(void (*start_func)(), enum sched_priority priority)
{
}

/*
This function picks up the next user thread from the user threads table,
according to the scheduling policy (explained later) and restores its
context. The context of a cooperative ULT is identical to the context field
in the xv6 PCB, which we’ve seen in the practical sessions.
Therefore, the context switch between the user threads can occur in the
same way as the regular context switch (look at swtch.S and uswtch.S).
If you are interested in understanding why the specific registers in the
context are saved, you can read about callee and caller saved registers.
After the context switch occurs, the newly selected thread will run the
code starting from the address stored by the ‘ra’ register in the same way
as in switching between two processes in the kernel.
*/
void uthread_yield()
{
}
/*
Terminates the calling user thread and transfers control to some other
user thread (similarly to yield). Don’t forget to change the terminated user
thread’s state to free. When the last user thread in the process calls
uthread_exit the process should terminate (i.e., exit(…) should be called).
*/
void uthread_exit()
{
}
/*
This function is called by the main user thread after it has created one or
more user threads. It is similar to yield; it picks the first user thread to run
according to the scheduling policy and starts it. If successful, this function
never returns, and any code beyond it will never be executed (much like
execvp).
Since the main user thread was not created using uthread_create, and
hence has no entry in the user thread table, its context will never be
restored. Any subsequent calls (after the user threads were already
started) to uthread_start_all should not succeed. In such a case, this
function should return -1 to indicate an error. Hint: this functionality can
be implemented u
*/
int uthread_start_all()
{
}
/*
This function sets the priority of the calling user thread to the
specified argument and returns the previous priority.
*/
enum sched_priority uthread_set_priority(enum sched_priority priority)
{
    enum sched_priority old_priority = uthread_self()->priority;
    uthread_self()->priority = priority;
    return old_priority;
}
/*
This function returns the current priority of the calling user thread.
Use the given enum defined in uthread.h for these functions.
*/
enum sched_priority uthread_get_priority()
{
    return uthread_self()->priority;
}
/*
Returns a pointer to the UTCB associated with the calling thread.
*/
struct uthread *uthread_self()
{
    return current_thread;
}
