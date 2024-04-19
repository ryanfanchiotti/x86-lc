/* C solution using gcc's popcount
int hammingDistance(int x, int y) {
    y ^= x;
    return __builtin_popcount(x);
} */

// at&t x86_64 solution
__attribute__((naked))
int hammingDistance(int x, int y) {
    __asm__(
        "xor %edi, %esi;"
        "popcnt %esi, %eax;"
        "ret;"
    );
}