#define STK_SIZE 256

typedef struct MyNode {
    int dl;
    int dr;
} MyNode;

//0ms version
bool isValid(char* s) {
    if (!s || !*s) {
        return true;
    }
    static MyNode stk1[STK_SIZE];
    static MyNode stk2[STK_SIZE];
    static MyNode stk3[STK_SIZE];
    unsigned int top1, top2, top3;
    int ch;

    top1 = top2 = top3 = STK_SIZE;
    while ((ch = *s++)) {
        switch (ch) {
        case '(':
            if (top1 <= STK_SIZE) {
                top1--;
                stk1[top1].dl = top2;
                stk1[top1].dr = top3;
                break;
            }
            return false;
        case ')':
            if (top1 < STK_SIZE) {
                if ((stk1[top1].dl == top2) && (stk1[top1].dr == top3)) {
                    top1++;
                    break;
                }
            }
            return false;
        case '[':
            if (top2 <= STK_SIZE) {
                top2--;
                stk2[top2].dl = top1;
                stk2[top2].dr = top3;
                break;
            }
            return false;
        case ']':
            if (top2 < STK_SIZE) {
                if ((stk2[top2].dl == top1) && (stk2[top2].dr == top3)) {
                    top2++;
                    break;
                }
            }
            return false;
        case '{':
            if (top3 <= STK_SIZE) {
                top3--;
                stk3[top3].dl = top1;
                stk3[top3].dr = top2;
                break;
            }
            return false;
        case '}':
            if (top3 < STK_SIZE) {
                if ((stk3[top3].dl == top1) && (stk3[top3].dr == top2)) {
                    top3++;
                    break;
                }
            }
            return false;
        default:
            break;
        }
    }
bail:
    return ((top1 == STK_SIZE) && (top2 == STK_SIZE) && (top3 == STK_SIZE));
}
