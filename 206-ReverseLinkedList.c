/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/* C solution
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev_node = NULL, * next_node;
    while (head) {
        next_node = head->next;
        head->next = prev_node;
        prev_node = head;
        head = next_node;
    }
    return prev_node;
} */

// at&t x86_64 solution
__attribute__((naked))
struct ListNode* reverseList(struct ListNode* head) {
    __asm__(
        "xor %rcx, %rcx;" // clear out regs used to store node ptrs
        "xor %rax, %rax;"
        
        "loop:;" // while cur node is not null
        "test %rdi, %rdi;"
        "je end;"

        "mov 8(%rdi), %rcx;" // store next node
        "mov %rax, 8(%rdi);" // reverse cur node's pointer
        "mov %rdi, %rax;" // move prev node up
        "mov %rcx, %rdi;" // move cur node up

        "jmp loop;"

        "end:;"
        "retq;"
    );
}