uint64
sys_calculate(void)
{
  int x, y;
  uint64 op_ptr, result_ptr;
  char op;

  // Get arguments from user space
  if(argint(0, &x) < 0 ||
     argint(1, &y) < 0 ||
     argaddr(2, &op_ptr) < 0 ||
     argaddr(3, &result_ptr) < 0)
    return -1;

  // Copy operator from user space
  if(copyin(myproc()->pagetable, &op, op_ptr, 1) < 0)
    return -1;

  int result;
  // Perform calculation based on operator
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
        return -1;  // Division by zero
      result = x / y;
      break;
    default:
      return -1;  // Invalid operator
  }

  // Copy result back to user space
  if(copyout(myproc()->pagetable, result_ptr, (char *)&result, sizeof(result)) < 0)
    return -1;

  return 0;
}