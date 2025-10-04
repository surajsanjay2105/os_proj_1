#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void run_test(int x, int y, char op) {
    int result;
    int error_code = calculate(x, y, &op, &result);
    if (error_code == 0) {
        printf("Input: {%d, %d, '%c'}, Output: %d, Return: %d\n", x, y, op, result, error_code);
    } else {
        printf("Input: {%d, %d, '%c'}, Output: n/a, Return: %d\n", x, y, op, error_code);
    }
}

int main(int argc, char *argv[]) {
    printf("--- Running calculate() tests ---\n");

    // {10, 4, '-'} -> 6, 0
    run_test(10, 4, '-');

    // {34, -9, '+'} -> 25, 0
    run_test(34, -9, '+');

    // {8, 12, '*'} -> 96, 0
    run_test(8, 12, '*');

    // {56, 6, '/'} -> 9, 0
    run_test(56, 6, '/');

    // {56, 6, '&'} -> n/a, -1
    run_test(56, 6, '&');

    // {5, 0, '/'} -> n/a, -1
    run_test(5, 0, '/');

    printf("--- Tests finished ---\n");
    
    exit(0);
}