#ifndef SET_H
#define SET_H

extern const void * Set;

void * Set_add (void * set, void * element);
void * Set_find (void * set, void * element);
int Set_contains(void * set, void * element);
void * Set_drop (void * set, void * element);
unsigned Set_count (void * set);

#endif
