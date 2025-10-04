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

  if(argint(0, &x) < 0 || argint(1, &y) < 0 || argaddr(3, &result_ptr) < 0)
    return -1;

  uint64 op_ptr;
  if(argaddr(2, &op_ptr) < 0)
    return -1;
  if(copyin(myproc()->pagetable, &op, op_ptr, 1) < 0)
    return -1;

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
        return -1;
      result = x / y;
      break;
    default:
      return -1;
  }

  if(copyout(myproc()->pagetable, result_ptr, (char*)&result, sizeof(result)) < 0)
    return -1;

  return 0;
}