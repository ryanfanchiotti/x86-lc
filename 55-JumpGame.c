/* C solution using concept of maximum gas from previous element
int canJump(int* nums, int numsSize) {
    int gas = 0;
    for (int i = 0; i < numsSize - 1; i++){
        gas--;
        if (gas < nums[i]) gas = nums[i];
        if (gas < 1) return 0;
    }
    return 1;
} */

// at&t x86_64 solution using registers as variables instead of stack frame
__attribute__((naked))
int canJump(int* nums, int numsSize){
    __asm__(
        "movl $1, %eax;" // move 1 into return register
        "xor %rdx, %rdx;" // init index to 0
        "xor %ecx, %ecx;" // init gas to 0
        "dec %esi;" // moving from last index will not be checked

        "loop:;"
        "cmp %edx, %esi;" // check if index is size - 1
        "jle end;"

        "dec %ecx;" // decrement gas after moving indices
        "cmpl (%rdi, %rdx, 4), %ecx;" // check if nums[i] has more gas
        "jge gascheck;"
        "movl (%rdi, %rdx, 4), %ecx;"

        "gascheck:;" // return false if no more gas
        "cmpl $1, %ecx;"
        "jge endloop;"
        "xor %eax, %eax;"
        "jmp end;"

        "endloop:;" // increment index and go back to start of loop
        "inc %edx;"
        "jmp loop;"

        "end:;"
        "ret;"
    );
}