#include <iostream>
#include <memory>

enum class Symbol
{
	S0, S1,
};

enum class State
{
	A, B, C, HALT
};

enum class Movement
{
	LOWER, HIGHER,
};

struct Instruction
{
	State currentState;
	Symbol inSymbol;
	Symbol outSymbol;
	Movement movement;
	State nextState;
};

using Program = Instruction*;
using Tape = Symbol*;
using Head = size_t;

struct Machine
{
	Tape tape = new Instruction[100];
	Head head;
};

int main()
{

	return 0;
}