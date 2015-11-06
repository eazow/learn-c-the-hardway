#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

RingBuffer *ringbuffer_create(int length)
{
    RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
    buffer->length = lenth;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = calloc(buffer->length, sizeof(char));

    return buffer;
}

void ringbuffer_destroy(RingBuffer *buffer)
{
    if(buffer) {
        free(buffer->buffer);
        free(buffer);
    }
}

int ringbuffer_write(RingBuffer *buffer, char *data, int length)
{
	if(ringbuffer_available_data(buffer) == 0) {
		buffer->start = buffer->end = 0;
	}

	check(length <= ringbuffer_available_space(buffer), "Not enough space: %d request, %d available", ringbuffer_available_data(buffer), length);

	void *result = memcpy(ringbuffer_ends_at(buffer), data, length);
	check(result != NULL, "Failed to write data into buffer.");

	ringbuffer_commit_write(buffer, length);

	return length;
error:
	return -1;
}

int ringbuffer_read(RingBuffer *buffer, char *target, int amount)
{
	check(amount <= ringbuffer_available_data(buffer), "Not enougn in the buffer: has %d, needs %d", ringbuffer_available(buffer), amount);

	void *result = memcpy(target, ringbuffer_starts_at(buffer), amount);
	check(result != NULL, "Failed to write buffer into data.");
	
	ringbufer_commit_read(buffer, amount);
	
	if(buffer->end == buffer->start) {
		buffer->start = buffer->end = 0;	
	}

	return amount;
error:
	return -1;
}

bstring ringbuffer_gets(RingBuffer *buffer, int amount)
{
	check(amount > 0, "Need more than 0 for gets, you gave: %d", amount);
	check(amount <= ringbuffer_available_data(buffer), "Not enough in the buffer.");

	bstring result = blk2bstr(ringbuffer_starts_at(buffer), amount);
	check(result != NULL, "Failed to create gets result.");
	check(blength(result) == amount, "Wrong result length.");

	ringbuffer_commit_read(buffer, amount);
	assert(ringbuffer_available_data(buffer) >= 0 && "Error in read commit.");

	return result;
error:
	return NULL;
}
