# Writing a Virtual Machine

- C compiler and GNU make are dependencies that will be heavily relied on for development and testing of the vm
- A basic knowledge of is necessary, from variables to functions and structures
- NOTE: there is no better way to learn something than to do it (build one)
- vm: is a software that emulates a physical computer
- Instruction set: these are commands that are executed on a CPU
- register: is a data holding place in a CPU
- this vm will A, B, C, D, E and F as general purpose registers. This implies that there are special purpose registers
- program: is a read-only sequence of instructions
- this is a stack-based vm. We can push and pop
- sample code
  ```asm
  PSH 5       ; pushes 5 to the stack
  PSH 10      ; pushes 10 to the stack
  ADD         ; pops two values on top of the stack, adds them pushes to stack
  POP         ; pops the value on the stack, will also print it for debugging
  SET A 0     ; sets register A to 0
  HLT         ; stop the program
  ```
- vm's work by following the instruction cycle: fetch, decode and execute
- the instructions to be executed are stored in an array as such the we can use an instruction pointer to point to the current instruction to execute
- the instruction pointer is the same as the program counter, a counter that is used to point to the current instruction to execute (PC/IP)
- a stack is a simple data structure that can be implemented with an array. This stack will be a fixed sized stack and the operations accepted will be push and pop.
- for the stack, we will need a stack pointer, sp
- this is how the stack will function

  ```asm
  [] // empty

  PSH 5 // put 5 on **top** of the stack
  [5]

  PSH 6 // 6 on top of the stack
  [5, 6]

  POP // pop the 6 off the top
  [5]

  POP // pop the 5
  [] // empty

  PSH 6 // push a 6...
  [6]

  PSH 5 // etc..
  [6, 5]
  ```

- so PSH and POP will be updating the sp
- when there is PSH, the next element in the program must be a value which will be pushed onto the stack. so with the ip pointing at `x`, then `x+1` will be a value
- POP, decrements the sp
- in a way it one shouldn't be bothered about actually popping (removing) from the stack since the value is either used or altered (on push)
- in the registers defined, using enum, the last register, which is not a register in this sense, is a register count (capacity). This will be used to create the register array
- relying on the register enum, we can use the enums to access the preferred register
-
