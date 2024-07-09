#include "stdio.h"

// mo-mac-vm instruction set
typedef enum
{
    PSH, // push (add) value onto the stack
    POP, // remove value from the stack
    ADD, // sum two values and push the result onto the stack
    HLT, // terminate the program
    MUL, // multiplication
    NEG, // negate a value
    SQR, // squares a number
    POW, // raise to the power, x is passed as value
    SHW, // print the stack to where the sp is
    DIF, // abs difference abs(b - a)
    SUB, // b - a
    SET, // assign a value to a registers
    SHR, // print the value in a register
    PSR, // push (add) value from a register onto the stack
    MOV, // move data from one register to another
    MVS, // move data from stack to register
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
    SET,
    A,
    10,
    SET,
    B,
    5,
    SHR,
    B,
    SHR,
    A,
    PSR,
    A,
    PSR,
    B,
    ADD,
    SHW,
    SHW,
    MVS,
    C,
    SHR,
    C,
    SHW,
    PSR,
    C,
    ADD,
    MVS,
    C,
    SHW,
    SHR,
    C,
    HLT,
    MOV,
    A,
    C,
    SHR,
    A,
    SHR,
    C,
    //
    PSH,
    5,
    SQR,
    SHW,
    // HLT,
    PSH,
    6,
    PSH,
    2,
    SHW,
    POW,
    SHW,
    // HLT,
    ADD,
    SHW,
    PSH,
    4,
    MUL,
    SHW,
    // POP,
    NEG,
    // HLT,
    PSH,
    1,
    PSH,
    -2,
    SHW,
    ADD,
    SHW,
    POP,
    SHW,
    SUB,
    SHW,
    PSH,
    -1,
    DIF,
    SHW,
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

void set()
{
    // ip should be pointing to the register and the next is the value
    const int reg = fetch();
    const int val = fetch();

    registers[reg] = val;
}

void push_from_reg_to_stack()
{
    // ip should be pointing to the register
    const int reg = fetch();
    const int value = registers[reg];

    push(value);
}

void mov()
{
    int reg1 = fetch();
    int reg2 = fetch();

    registers[reg2] = registers[reg1];
}

void move_from_stack_to_reg()
{
    int reg = fetch();

    registers[reg] = stack[sp];
}

void print_stack()
{
    for (int i = 0; i < sp + 1; i++)
    {
        printf("%d-> %d\n", i, stack[i]);
    }
}

void print_register()
{
    const int reg = fetch();
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

    case SHW:
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

    case SET:
        set();
        break;

    case SHR:
        print_register();
        break;

    case PSR:
        push_from_reg_to_stack();
        break;

    case MOV:
        mov();
        break;

    case MVS:
        move_from_stack_to_reg();
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
