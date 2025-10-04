#include "types.h"
#include "riscv.h"
#include "defs.h"

uint64
sys_calculate(void)
{
  int x, y;
  char op;
  uint64 result_ptr;
  int result;

  // Get arguments from user space
  if(argint(0, &x) < 0 || argint(1, &y) < 0 || argaddr(3, &result_ptr) < 0)
    return -1;

  // Get operator from user space
  uint64 op_ptr;
  if(argaddr(2, &op_ptr) < 0)
    return -1;
  if(copyin(myproc()->pagetable, &op, op_ptr, 1) < 0)
    return -1;

  // Validate operator and perform calculation
  switch(op) {
    case '+':
      result = x + y;
      break;
    case '-':
      result = x - y;
      break;
    case '*':
      result = x * y;
      break;
    case '/':
      if(y == 0)
        return -1;  // Division by zero error
      result = x / y;
      break;
    default:
      return -1;  // Invalid operator
  }

  // Copy result back to user space
  if(copyout(myproc()->pagetable, result_ptr, (char*)&result, sizeof(result)) < 0)
    return -1;

  return 0;
}