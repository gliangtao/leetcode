/*
Given a non-negative number represented as an array of digits, plus one to the number.

The digits are stored such that the most significant digit is at the head of the list.
*/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
//0ms version, O(n)
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int* ret = NULL;
    int retSize = 0;
    if (!digits || (digitsSize < 0)) goto bail;
    int* p = digits, *q = digits + digitsSize;
    while (!*p && (p < q)) p++;
    digitsSize += (digits - p);
    digits = p;

    retSize = (digitsSize && ((digits[0] < 9) || (digits[digitsSize - 1] < 9))) ? digitsSize : (digitsSize + 1);
    ret = (int*)malloc(sizeof(int) * retSize);
    if (!ret) goto bail;
    int i, d, carry = 1;

    ret[0] = 0;
    for (p = ret + retSize - 1, q = digits + digitsSize - 1, i = digitsSize; i > 0; i--) {
        d = (*q-- + carry);
        if (d < 10) {
            *p-- = d;
            carry = 0;
        } else {
            carry = 1;
            *p-- = d - 10;
        }
    }

    if (carry) ret[0] += 1;

bail:
    if (returnSize) *returnSize = retSize;
    return ret;
}
