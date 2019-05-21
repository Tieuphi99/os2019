#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 10

typedef struct product
{
	char type;  // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit;  // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void initFriedChicken(item *init)
{
	init->type = 0;
	init->amount = 0;
    init->unit = 0;
}

void initFrenchFries(item *init)
{
    init->type = 1;
    init->amount = 0;
    init->unit = 1;
}

void produce(item *i)
{
	while ((first + 1) % BUFFER_SIZE == last)
	{
    //do nothing -- no free buffer item
		return;
	}
	memcpy(&buffer[first], i, sizeof(item));
	i->amount += 1;
	first = (first + 1) % BUFFER_SIZE;
    printf("First = %d\n", first);
}

item *consume()
{
	item *i = malloc(sizeof(item));
	while (first == last)
	{
    //do nothing -- nothing to consume
        return;
	}
	memcpy(i, &buffer[last], sizeof(item));
	i->amount -= 1;
	last = (last + 1) % BUFFER_SIZE;
	printf("Last = %d\n", last);
	return i;
}

void *prodThread(void* param)
{
    item *chicken, fried;
	chicken = &fried;
    initFriedChicken(chicken);
    produce(chicken);
    produce(chicken);
    produce(chicken);
    pthread_exit(NULL);
}

void *consThread(void* param)
{
    consume();
	consume();
	pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    printf("==-prodThread-==\n");
    pthread_create(&tid, NULL, prodThread, NULL);
    pthread_join(tid, NULL);
    printf("==-consThread-==\n");
    pthread_create(&tid, NULL, consThread, NULL);
    pthread_join(tid, NULL);
    pthread_exit(NULL);
}
