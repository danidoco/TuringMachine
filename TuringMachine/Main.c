#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define INITIAL_STATE STATE_A
#define TAPE_SIZE 26
#define INITIAL_FILL_SYMBOL 0
#define INITIAL_HEAD 1

enum State
{
	STATE_HALT = 0,
	STATE_A = 'A',
	STATE_B = 'B',
	STATE_C = 'C',
};

enum Move
{ 
	MOVE_L = 0,
	MOVE_N = 1, 
	MOVE_R = 2,
};

struct Rule
{
	int state;
	int read;
	int write;
	int move;
	int next;
};

static void PrintMachineDump(int state, int* tape, unsigned int head)
{
	if (state == STATE_HALT) printf("[HALT] ");
	else printf("[%c   ] ", state);

	for (int i = 0; i < TAPE_SIZE; i++)
	{
		if (i == head) printf("{%d}", tape[i]);
		else printf(" %d ", tape[i]);
	}

	fputc('\n', stdout);
}

int main()
{
	int state = INITIAL_STATE;
	
	int tape[TAPE_SIZE] = { 0, 1, 2, 3, 1, 3, 2, 1, 1, 1, 2, 3, 1, 3, 2, 1, 1, 1, 2, 3, 1, 3, 2, 1, 1, 0 };
	tape[TAPE_SIZE - 1] = 0;

	unsigned int head = INITIAL_HEAD;

	struct Rule table[] =
	{
		{ STATE_A, 1, 2, MOVE_R, STATE_A },
		{ STATE_A, 2, 3, MOVE_R, STATE_A },
		{ STATE_A, 3, 4, MOVE_R, STATE_A },
		{ STATE_A, 4, 5, MOVE_R, STATE_A },
		{ STATE_A, 5, 6, MOVE_R, STATE_A },
		{ STATE_A, 6, 7, MOVE_R, STATE_A },
		{ STATE_A, 7, 8, MOVE_R, STATE_A },
		{ STATE_A, 8, 9, MOVE_R, STATE_A },
		{ STATE_A, 9, 9, MOVE_N, STATE_HALT },
		{ STATE_A, 0, 0, MOVE_L, STATE_B },
		{ STATE_B, 1, 2, MOVE_L, STATE_B },
		{ STATE_B, 2, 3, MOVE_L, STATE_B },
		{ STATE_B, 3, 4, MOVE_L, STATE_B },
		{ STATE_B, 4, 5, MOVE_L, STATE_B },
		{ STATE_B, 5, 6, MOVE_L, STATE_B },
		{ STATE_B, 6, 7, MOVE_L, STATE_B },
		{ STATE_B, 7, 8, MOVE_L, STATE_B },
		{ STATE_B, 8, 9, MOVE_L, STATE_B },
		{ STATE_B, 9, 9, MOVE_N, STATE_HALT },
		{ STATE_B, 0, 0, MOVE_R, STATE_A },
	};

	bool running = true;

	while (running)
	{
		PrintMachineDump(state, &tape, head);

		for (int i = 0; i < sizeof(table) / sizeof(struct Rule); i++)
		{
			struct Rule* rule = &table[i];

			if (state == STATE_HALT)
			{
				running = false;
			}

			if (state == rule->state && tape[head] == rule->read)
			{
				tape[head] = rule->write;
				head += rule->move - 1;
				state = rule->next;
				break;
			}
		}
	}

	return 0;
}
