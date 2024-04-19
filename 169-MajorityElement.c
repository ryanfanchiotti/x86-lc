/* C solution using Boyer-Moore majority vote algorithm
int majorityElement(int* nums, int numsSize) {
    int votes = 1, cur = *nums;
    for (int i = 1; i < numsSize; i++){
        if (votes == 0){
            cur = nums[i];
            votes++;
        } else if (cur == nums[i]) votes++;
        else votes--;
    }
    return cur;
} */

// at&t x86_64 solution using stack frame
__attribute__((naked)) 
int majorityElement(int* nums, int numsSize) {
    __asm__(
    "pushq %rbp;" // push frame pointer onto stack
    "sub $16, %rsp;" // creating stack space for votes, index, and cur
    "movq $1, -8(%rbp);" // init votes to 1
    "movq $1, -16(%rbp);" // init index to 1
    "movl (%rdi), %eax;" // init cur to nums[0], storing it in return register

    "loop:;" 
    "cmpl %esi, -16(%rbp);" // while index is less than size
    "jge end;"
    "mov -16(%rbp), %rcx;" // move index to rcx and index into nums
    "mov (%rdi, %rcx, 4), %edx;" // move nums[i] to edx
    
    "votescheck:;" // check if votes is 0
    "cmpq $0, -8(%rbp);"
    "jne curcheck;"
    "movq $1, -8(%rbp);" // set votes to 1 and move nums[i] to cur
    "movl %edx, %eax;"
    "jmp endloop;"
    
    "curcheck:;" // check if cur is equal to nums[i]
    "cmpl %eax, %edx;" // only need to check low end of regs since int
    "jne decrementvotes;"
    "addq $1, -8(%rbp);" // increment votes for cur
    "jmp endloop;"

    "decrementvotes:;"
    "subq $1, -8(%rbp);" // decrement votes for cur

    "endloop:;" // increment index and go to start of loop
    "addq $1, -16(%rbp);"
    "jmp loop;"

    "end:;"
    "add $16, %rsp;" // clean up stack and return
    "popq %rbp;"
    "retq;" 
    );
}