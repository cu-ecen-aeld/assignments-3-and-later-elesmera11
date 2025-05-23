#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    // cast the parameter to the thread_data structure
    struct thread_data* thread_func_args = (struct thread_data *)(thread_param);
    // return success=false by default
    thread_func_args->thread_complete_success = false;
    if(usleep(thread_func_args->wait_to_obtain_ms * 1000) != 0) {
        ERROR_LOG("usleep interrupted");
        return thread_param;
    }
    if(pthread_mutex_lock(thread_func_args->mutex) != 0) {
        ERROR_LOG("pthread_mutex_lock failed");
        return thread_param;
    }
    if(usleep(thread_func_args->wait_to_release_ms * 1000) != 0) {
        ERROR_LOG("usleep interrupted");
        pthread_mutex_unlock(thread_func_args->mutex);
        return thread_param;
    }
    if(pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        ERROR_LOG("pthread_mutex_unlock failed");
        return thread_param;
    }
    thread_func_args->thread_complete_success = true;

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    return (void *)(thread_func_args);
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    if (thread == NULL || mutex == NULL) {
        ERROR_LOG("thread or mutex is NULL");
        return false;
    }

    struct thread_data * thread_param = (struct thread_data *)(malloc(sizeof(struct thread_data)));
    thread_param->mutex = mutex;
    thread_param->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_param->wait_to_release_ms = wait_to_release_ms;
    thread_param->thread_complete_success = false;
    if (pthread_create(thread, NULL, threadfunc, (void *)(thread_param)) != 0) {
        ERROR_LOG("pthread_create failed");
        free(thread);
        return false;
    } else {
        DEBUG_LOG("Thread created successfully");
        return true;
    }
        /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    return false;
}

