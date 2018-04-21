//mypthread.c

#include "mypthread.h"

//Global
linked_list ll;
int current_tid = 1; 

mypthread_t* create_linked_list()
{
	ll->thread = NULL; 
	ll->size = 0; 
}

void add_thread(mypthread_t* thread)
{
	int i; 
	mythread_t* init = head; 
	while(1)
	{
		if(init->tid == NULL)
		{
			init = thread; 
			ll->size++; 
			return; 
		}
		init = init->next_thread; 
	}
}

mypthread_t* search(tid)
{
	mypthread_t* i = head; 
	while(i->tid != NULL)
	{
		if(i->tid == tid)
		{
			return i; 
		}
		i = i->next_thread; 
	}
	
	printf("Error, tid does not exist");
	return; 
}

mypthread_t* find_active(mypthread_t* thread)
{
	mypthread_t* i = head; 
	while(i->tid != NULL)
	{
		if(i->status == RUNNING)
		{
			return i; 
		}
		i = i->next_thread; 
	}
	
	mypthread_t* error; 
	error->tid = 0; 
}


//  Write your thread create function here...
int mypthread_create(mypthread_t* *thread, const mypthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
	if (ll->size == 0)
	{
		create_linked_list();  
		mypthread_t** main_t = (mypthread_t**)malloc(sizeof(mypthread_t*));  
		main_t->tid = 1; 
		ucontext_t* main_context = (ucontext_t*)malloc(sizeof(ucontext_t)); 
		main_context->uc_stack.ss_sp = (char*) malloc(sizeof(char) * 16384);
		main_context->uc_stack.ss_size = 16384; 
		main_t->context = main_context; 
		main_t->status = RUNNING; 
		add_thread(main_t); 
	}
	
	thread->tid = ll->size + 1; 
	thread->context = (ucontext_t*)malloc(sizeof(ucontext_t));
	getcontext(thread->context); 
	thread->context->uc_stack.ss_sp = (char*) malloc(sizeof(char) * 16384);
	thread->mynode->context->uc_stack.ss_size = 16384; 
	thread->status = RUNNING; 
	makecontext(thread->context, void *(*start_routine), void *arg); 
	add_thread(thread); 
}	
	
// Write your thread exit function here...
void mypthread_exit (void *retval)
{
	mypthread_t* thread = search(current_tid); 
	thread->status = DEAD; 
	if(thread->join != 0)
	{
		//unblock the other thread
		other_thread = search(thread->join); 
		other_thread->state = RUNNING; 
	}
	mypthread_t* replacement = find_active(); 
	if(replacement == NULL) return; 
	else
	{
		current_tid = replacement->tid; 
		setcontext(replacement); 
	}
}
 
// Write your thread yield function here...
int mypthread_yield (void)
{
	mypthread_t* current_thread = search(current_tid); 
	current_thread->status = BLOCKED; 
	mypthread_t* replacement = find_active(); 
	current_thread->status = RUNNING; 
	if (replacement->tid == 0) return 0; 
	current_tid = replacement->tid; 
	swapcontext(current_thread->context, replacement->context); 
}

//  Write your thread join function here...
int mypthread_join (mypthread_t* thread, void **retval)
{
	if(thread->status != RUNNING) return 0; 
	mypthread_t* current_thread = search(current_tid); 
	current_thread->status = BLOCKED; 
	thread->join = current_thread->tid; 
	current_tid = thread->tid; 
	swapcontext(current_thread ->context, thread->context); 
}
    
