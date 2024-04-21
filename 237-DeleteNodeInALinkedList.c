/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

/* C solution swapping node values
void deleteNode(struct ListNode* node) {
    struct ListNode* n = node->next, * p = NULL; 
    while (n){
        int temp = node->val;
        node->val = n->val;
        n->val = temp;
        p = node;
        node = n;
        n = n->next;
    }
    p->next = NULL;
} */

// at&t x86_64 solution
// this can be done only swapping two nodes, wanted practice swapping through the entire list
// nodes don't seem to be malloced so no need to free node that's being removed
__attribute__((naked))
void deleteNode(struct ListNode* node){
    __asm__(
        "mov 8(%rdi), %r8;" // storing next node in r8
        "xor %r9, %r9;" // storing prev node in r9

        "loop:;" // while next node isn't null
        "cmpq $0, %r8;"
        "je end;"

        "mov (%rdi), %eax;" // moving current node contents to eax
        "mov (%r8), %ecx;" // moving next node contents to ecx
        "mov %eax, (%r8);" // swapping node contents
        "mov %ecx, (%rdi);"
        "mov %rdi, %r9;" // move current node to prev node
        "mov %r8, %rdi;" // move next node to current node
        "mov 8(%r8), %r8;" // move next node to next next node

        "jmp loop;" 

        "end:;"
        "movq $0, 8(%r9);" // set next pointer of prev node to null
        "ret;"
    );
}