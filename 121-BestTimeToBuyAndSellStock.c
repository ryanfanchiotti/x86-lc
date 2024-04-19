/* C solution keeping track of minimum price
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 1) return 0;
    int min_price = prices[0], profit = 0;
    for (int i = 1; i < pricesSize; i++){
        int num = prices[i];
        if ((num - min_price) > profit) profit = (num - min_price);
        if (min_price > num) min_price = num;
    }
    return profit;
} */

// at&t x86_64 solution
__attribute__((naked))
int maxProfit(int* prices, int pricesSize) {
    __asm__(
        "cmpl $1, %esi;" // checking if pricesSize is 1
        "jne afterbase;"
        "xor %eax, %eax;" // returning 0 if so
        "ret;"

        "afterbase:;"
        "movq $1, %rdx;" // init index to 1
        "movl (%rdi), %ecx;" // init min_price to prices[0]
        "xor %r10, %r10;" // init profit to 0
        "xor %r9, %r9;" // cleaning up registers that will be used later

        "loop:;" // loop until index is size of prices
        "cmpl %edx, %esi;"
        "jle end;"

        "movl (%rdi, %rdx, 4), %eax;" // move prices[i] to eax
        "movslq %eax, %r9;" 
        "sub %rcx, %r9;" // compute prices[i] - min_price
        "cmp %r9, %r10;" // check if profit is greater than current max
        "jge aftercheck1;"
        "mov %r9, %r10;" // store if so
        
        "aftercheck1:;" // compare min_price to num
        "cmpl %eax, %ecx;"
        "jle aftercheck2;"
        "mov %eax, %ecx;"

        "aftercheck2:;" // increment index
        "inc %edx;"
        "jmp loop;"
        
        "end:;" // move profit to return register
        "mov %r10, %rax;"
        "ret;"
    );
}