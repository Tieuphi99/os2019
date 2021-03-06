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
	return i;
}

int main()
{
	int option = 0;
	item *chicken, fried, *fries, french;
	chicken = &fried;
	fries = &french;
    printf("1 = Fried Chicken\n");
    printf("2 = French Fries\n");
    printf("=====================\n");
	while (true)
	{
		scanf("%d", &option);
		if (option == 1)
		{
			printf("2 Fried Chicken\n");
			initFriedChicken(chicken);
			produce(chicken);
            produce(chicken);
			chicken = consume();
			break;
		}
		else if (option == 2)
		{
			printf("2 French Fries\n");
			initFries(fries);
            produce(fries);
            produce(fries);
            fries = consume();
			break;
		}
		else
		{
			printf("ERROR\n");
            printf("1 = Fried Chicken\n");
            printf("2 = French Fries\n");
            printf("=====================\n");
		}
	}
	return 0;
}
