#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void list_node_swap(ListNode *a, ListNode *b)
{
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
}

int list_bubble_sort(List *list, list_compare cmp)
{
	int sorted = 1;

	if(list_count(list) <= 1) {
		return 0;
	}

	do {
		sorted = 1;
		ListNode *cur = NULL;
		for(cur = list->first; cur!=NULL; cur = cur->next) {
			if(cur->next) {
				if(cmp(cur->value, cur->next->value) > 0) {
					list_node_swap(cur, cur->next);
					sorted = 0;
				}  
			}
		}
	}
	while(!sorted);

	return 0;
}