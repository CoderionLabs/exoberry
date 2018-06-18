#include <string.h>

#include <debug.h>
#include <message.h>
#include <timing.h>

#include <malloc.h>
// use lk's libc malloc
#define MEM_LIBC_MALLOC 1

dsm_message *dsm_message_create(int head_size, int tail_size){
    dsm_message *msg = malloc(sizeof(dsm_message));
    if(!msg){return NULL;}

    get_monotonic_time(&msg->created);

    msg->buffer_size = head_size + tail_size;

    msg->buffer = malloc(msg->buffer_size);
    if(!msg->buffer){
        free(msg);
        return NULL;
    }

    msg->data = msg->buffer + head_size;
    msg->head_size = head_size;
    msg->data_size = 0;
    msg->tail_size = tail_size;
    msg->next = NULL;

    return msg;
}

int dsm_message_resize(dsm_message *msg, int new_head_size, int new_tail_size){
    char *old_buffer = msg->buffer;
    int old_buffer_size = msg->buffer_size;
    int old_head_size = msg->head_size;

    msg->buffer_size = new_head_size + msg->data_size + new_tail_size;
    msg->buffer = malloc(msg->buffer_size);
    if(!msg->buffer){
        dsm_message_destroy()
    }
}