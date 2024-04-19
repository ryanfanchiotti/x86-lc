/* C solution with loop
int xorOperation(int n, int start) {
    int ans = start;
    for (int i = 1; i < n; i++) ans ^= (i * 2) + start;
    return ans;
} */

// at&t x86_64 solution
__attribute__((naked))
int xorOperation(int n, int start) {
    __asm__(
        "xor %ecx, %ecx;"
        "inc %ecx;" // init index to 1
        "movl %esi, %eax;" // init ans to start

        "loop:;"
        "cmpl %ecx, %edi;" // check if index reaches n
        "jle end;"

        "movl %ecx, %edx;" // multiply index by 2 and add start
        "imul $2, %edx;"
        "add %esi, %edx;"
        "xor %edx, %eax;" // xor this value with ans

        "inc %ecx;" // increment index
        "jmp loop;"

        "end:"
        "ret;"
    );
}