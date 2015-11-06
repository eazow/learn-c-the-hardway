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

#define ringbuffer_available_data(B) (((B)->end+1)%(B)->length - (B)->start - 1)

#define ringbuffer_available_space(B) ((B)->length - (B)->end -1)

#define ringbuffer_full(B) (ringbuffer_available_data((B)) - (B)->length == 0)

#define ringbuffer_empty(B) (ringbuffer_available_data((B)) == 0)

#define ringbuffer_puts(B, D) ringbuffer_write((B), bdata((D)), blength((D)))

#define ringbuffer_get_all(B) ringbuffer_gets((B), ringbuffer_available_data((B)))

#define ringbuffer_starts_at(B) ((B)->buffer + (B)->start)

#define ringbuffer_ends_at(B) ((B)->buffer + (B)->end)

#define ringbuffer_commit_read(B, A) ((B)->start = ((B)->start + (A)) % (B)->length)

#define ringbuffer_commit_write(B, A) ((B)->end = ((B)->end +(A)) % (B)->length)

#endif
