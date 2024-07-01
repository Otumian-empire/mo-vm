#include "stdio.h"

// mo-mac-vm instruction set
typedef enum
{
    PSH, // push (add) value onto the stack
    POP, // remove value from the stack
    ADD, // sum two values and push the result onto the stack
    SET, // assign a value onto a registers
    HLT, // terminate the program
    // we can add our later when we understand this
    // MOV, // move data from one register to another
    // MVS, // move data from stack to register
    MUL,  // multiplication
    NEG,  // negate a value
    SQR,  // squares a number
    POW,  // raise to the power, x is passed as value
    SHOW, // print the stack to where the sp is
    DIF,  // abs difference abs(b - a)
    SUB,  // b - a
    // etc
} InstructionSet;

// registers
typedef enum
{
    A,
    B,
    C,
    D,
    E,
    F,
    NUM_OF_REGISTERS
} Registers;

// sample test program
const int program[] = {
    PSH,
    5,
    SQR,
    SHOW,
    // HLT,
    PSH,
    6,
    PSH,
    2,
    SHOW,
    POW,
    SHOW,
    // HLT,
    ADD,
    SHOW,
    PSH,
    4,
    MUL,
    SHOW,
    // POP,
    NEG,
    // HLT,
    PSH,
    1,
    PSH,
    -2,
    SHOW,
    ADD,
    SHOW,
    POP,
    SHOW,
    SUB,
    SHOW,
    PSH,
    -1,
    DIF,
    SHOW,
    HLT,
};

// instruction pointer
int ip = 0;

// when to terminate the loop (going through the program - instructions)
int running = 1;

// set the stack pointer to point to -1 since nothing is in the stack
// and 0 points to the first item
int sp = -1;
int stack[256];

// registers
int registers[NUM_OF_REGISTERS];

// get the current instruction
int fetch()
{
    const int instruction = program[ip];
    ip++; // increment instruction pointer

    return instruction;
}

void push(int value)
{
    sp++;
    stack[sp] = value;
    printf("pushed (%d): %d\n", sp, stack[sp]);
}

int pop()
{
    int r = sp;
    sp--;
    printf("popped (%d): %d\n", r, stack[r]);
    return stack[r];
}

void add()
{
    // add is a binary operator, so we pop the stack twice
    int a = pop();
    int b = pop();

    int result = a + b;

    // push result onto the stack
    push(result);
}

void halt()
{
    running = 0;
}

void mul()
{
    // mul is a binary operator, so we pop the stack twice
    int a = pop();
    int b = pop();

    int result = a * b;

    // push result onto the stack
    push(result);
}

void neg()
{
    // neg is a unary operator, so we pop the stack once
    int a = pop();

    int result = a * -1;

    // push result onto the stack
    push(result);
}

void sqr()
{
    int a = pop();

    int result = a * a;

    // push result onto the stack
    push(result);
}

void pow_()
{
    // this is in the form b^a, b exponent a
    int a = pop();
    int b = pop();

    int result = b;

    // must be >= 1 all the time or force it
    if (a < 1)
    {
        a = 1;
    }

    if (a == 1)
    {
        push(result);
    }

    for (int i = 1; i < a; i++)
    {
        result *= b;
    }

    // push result onto the stack
    push(result);
}

void dif()
{
    int a = pop();
    int b = pop();

    int result = b - a;

    if (result < 0)
    {
        result *= -1;
    }

    push(result);
}

void sub()
{
    int a = pop();
    int b = pop();

    int result = b - a;

    push(result);
}

void print_stack()
{
    for (int i = 0; i < sp + 1; i++)
    {
        printf("%d-> %d\n", i, stack[i]);
    }
}

void print_register(int reg)
{
    printf("reg(%d)-> %d\n", reg, registers[reg]);
}

void eval(int instr)
{
    switch (instr)
    {
    case HLT:
        halt();
        break;

    case PSH:
        // push the next instruction which is a value from the program
        push(fetch());
        break;

    case POP:
        pop();
        break;

    case ADD:
        add();
        break;

    case MUL:
        mul();
        break;

    case NEG:
        neg();
        break;

    case SHOW:
        print_stack();
        break;

    case SQR:
        sqr();
        break;

    case POW:
        pow_();
        break;

    case DIF:
        dif();
        break;

    case SUB:
        sub();
        break;

    default:
        break;
    }
}

int main()
{
    while (running == 1)
    {
        // get the current instruction
        // evaluate current instruction
        eval(fetch());
        // printf("IP: %d\n", instr); // print out current instruction
    }

    // print_stack();

    return 0;
}
