/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/* C solution
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (!root || root->val == val) return root;
    return (val < root->val ? searchBST(root->left, val) : searchBST(root->right, val));
} */

// at&t x86_64 solution using recursion
__attribute__((naked))
struct TreeNode* searchBST(struct TreeNode* root, int val) {
    __asm__(
        "test %rdi, %rdi;" // checking if root is null
        "jne after1;"
        "movq $0, %rax;" // returning null if so
        "ret;"

        "after1:"
        "cmpl (%rdi), %esi;" // checking if val is equal to root val
        "jne after2;"
        "movq %rdi, %rax;" // returning root if so
        "ret;"
        
        "after2:"
        "cmpl (%rdi), %eax;" // check if val is less than root val
        "jge right;"
        "mov 8(%rdi), %rdi;" // move left node to root for func call
        "jmp end;"

        "right:;"
        "mov 16(%rdi), %rdi;"  // move right node to root for func call

        "end:;"
        "call searchBST;" // call self
        "ret;"
    );
} 