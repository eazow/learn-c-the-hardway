#ifndef _lcthw_ringbuffer_h
#define _lcthw_ringbuffer_h

#include <lcthw/bstrlib.h>

typedef struct {
    char *buffer;
    int length;
    int start;
    int end;
} RingBuffer;

RingBuffer *ringbuffer_create(int length);

void ringbuffer_destroy(RingBuffer *buffer);

int ringbuffer_read(RingBuffer *buffer, char *target, int amount);

int ringbuffer_write(RingBuffer *buffer, char *data, int length);

int ringbuffer_empty(RingBuffer *buffer);

int ringbuffer_full(RingBuffer *buffer);

int ringbuffer_available_data(RingBuffer *buffer);

int ringbuffer_available_space(RingBuffer *buffer);

bstring ringbuffer_gets(RingBuffer *buffer, int amount);

#endif
