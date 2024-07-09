# MO-MAC-VM

A replication of the mac-vm by [MAC github](https://web.archive.org/web/20200913182033/https://github.com/felixangell/mac) following [MAC article](https://web.archive.org/web/20200121100942/https://blog.felixangell.com/virtual-machine-in-c/)

## INSTRUCTION AND HOW THEY WORK

- **PSH**: Push (add) value onto the stack, `PSH 5`
- **POP**: Remove value from the stack, `POP`
- **ADD**: Sum two values and push the result onto the stack, `ADD`
- **HLT**: Terminate the program, `HLT`
- **MUL**: Multiply two values and push the result onto the stack, `MUL`
- **NEG**: Negate a value and push the result onto the stack, `NEG`
- **SQR**: Square a value and push the result onto the stack, `SQR`
- **POW**: Raise a value to the power of another value and push the result onto the stack, `POW`
- **SHW**: Print the stack to where the SP is, `SHW`
- **DIF**: Calculate the absolute difference between two values and push the result onto the stack
- **SUB**: Subtract one value from another and push the result onto the stack, b - a, `SUB`
- **SET**: Assign a value to a register (directly), `SET REG VAL`
- **SHR**: Print the value in a register, `SHR REG`
- **PSR**: Push (add) value from a register onto the stack, `PSR REG`
- **MOV**: Move data from one register to another, `MOV REG1 REG2`, from `REG2` to `REG1`
- **MVS**: Move data from stack to register, `MVS REG`

<!-- TODO -->

EQ: checks if two values are equal and pushes 1 onto the stack if true, 0 otherwise.
NE: checks if two values are not equal and pushes 1 onto the stack if true, 0 otherwise.
LT: checks if the first value is less than the second and pushes 1 onto the stack if true, 0 otherwise.
GT: checks if the first value is greater than the second and pushes 1 onto the stack if true, 0 otherwise.
LE: checks if the first value is less than or equal to the second and pushes 1 onto the stack if true, 0 otherwise.
GE: checks if the first value is greater than or equal to the second and pushes 1 onto the stack if true, 0 otherwise.
