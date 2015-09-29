#if 0
//Invalid version
typedef struct MinStackElem_S {
    struct MinStackElem_S* parent;
    struct MinStackElem_S* left;
    struct MinStackElem_S* right;
    int size;
    int x;
} MinStackElem;

typedef struct MinStack__ {
    MinStackElem* elems;
    MinStackElem* me;
    int top;
    int maxSize;
} MinStack;

void minStackCreate(MinStack *stack, int maxSize) {
    if (stack) {
        stack->maxSize = maxSize;
        stack->top = -1;
        stack->elems = (maxSize > 0) ? (MinStackElem*)malloc(sizeof(MinStackElem) * maxSize) : NULL;
        if (stack->elems == NULL) {
            stack->maxSize = 0;
        }
        stack->me = NULL;
    }
}

static void insertElem(MinStack* stack, MinStackElement* e) {
    MinStackElem* p = stack->me;
    MinStackElem* q;
    int x = e->x;
    e->left = NULL;
    e->right = NULL;
    e->parent = NULL;
    e->size = 1;
    while (p != NULL) {
        if (e->x <= p->x) {
            // e replaces p, p becomes child of e
            if (p->parent == NULL) {
                stack->me = e;
                return;
            }
            e->parent = p->parent;
            e->left = p;
            if (p->parent->left == p) {
                p->parent->left = e;
            } else {
                p->parent->right = e;
            }
            p->parent = e;
            e->size += p->size;
            for (q = e->parent; q != NULL; q = q->parent) {
                q->size++;
            }
        } else {
            if (!p->left) {
                p->left = e;
                e->parent = p;
                break;
            } else if (!p->right) {
                p->right = e;
                e->parent = p;
                break;
            } else if (p->left->size <= p->right->size) {
                p = p->left;
            } else {
                p = p->right;
            }
        }
    }
}

static void removeElem(MinStack* stack, MinStackElement* e) {
    MinStackElem *p, *q;
    if (!e) {
        return;
    }
    p = stack->min;
    if (p->size == 1) {
        stack->min = NULL;
        return;
    }
    parent = e->parent;
    if (e->left == NULL) {
        q = e->right;
    } else if (e->right == NULL) {
        q = e->right;
    } else if (e->left->size <= e->right->size) {
        q = e->right;
    } else {
        q = e->left;
    }
    if (parent != NULL) {
        if (parent->left == e) {
            parent->left = q;
        } else {
            parent->right = q;
        }
    }
    if (q != NULL) {
        q->parent = parent;
    }
    while (parent != NULL) {
        parent->size--;
        parent = parent->parent;
    }
}

void minStackPush(MinStack *stack, int element) {
    if ((stack) && (stack->top < stack->maxSize - 1)) {
        stack->top++;
        MinStackElem* top = stack->elems + stack->top;
        top->x = element;
        MinStackElem* pMin = stack->minElem;
        MinStackElem* pPrev;
        if (!pMin) {
            stack->minElem = stack->elems + stack->top;
        } else {
            pPrev = pMin;
            while ((pMin != NULL) && (pMin->x < element)) {
                pPrev = pMin;
                pMin = pMin->next;
            }
            if (pPrev == pMin) {
                stack->minElem = top;
            } else {
                pPrev->next = top;
            }
        }
        top->next = pMin;
    }
}

void minStackPop(MinStack *stack) {
    if (stack) {
        if (stack->top >= 0) {
            MinStackElem* top = stack->elems + stack->top;
            int x = top->x;
            MinStackElem* pMin = stack->minElem;
            if (top == stack->minElem) {
                stack->minElem = top->next;
            } else {
                MinStackElem* pNext = pMin->next;
                while (pNext != top) {
                    pMin = pNext;
                    pNext = pNext->next;
                }
                pMin->next = top->next;
            }
            stack->top--;
        }
    }
}

int minStackTop(MinStack *stack) {
    if ((stack) && (stack->top >= 0)) {
        return stack->elems[stack->top].x;
    }
    return INT_MAX;
}

int minStackGetMin(MinStack *stack) {
    if (stack && stack->minElem) {
        return stack->minElem->x;
    }
    return INT_MAX;
}

void minStackDestroy(MinStack *stack) {
    if (stack) {
        free(stack->elems);
    }
}

#endif

//12ms accepted version
typedef struct MinStack__ {
    int* es;
    int* mes;
    int top;
    int mtop;
    int maxSize;
} MinStack;

void minStackCreate(MinStack *stack, int maxSize) {
    if (stack) {
        stack->maxSize = maxSize;
        stack->top = -1;
        stack->mtop = -1;
        if (maxSize > 0) {
            stack->es = (int*)malloc(sizeof(int) * maxSize * 2);
            stack->mes = stack->es + maxSize;
        }
    }
}

void minStackPush(MinStack *stack, int element) {
    if ((stack) && (stack->top < stack->maxSize - 1)) {
        stack->es[++stack->top] = element;
        if (stack->mtop < 0) {
            stack->mtop = 0;
            stack->mes[0] = element;
        } else if (element <= stack->mes[stack->mtop]) {
            stack->mes[++stack->mtop] = element;
        }
    }
}

void minStackPop(MinStack *stack) {
    if ((stack) && (stack->top >= 0)) {
        int tope = stack->es[stack->top--];
        if (tope <= stack->mes[stack->mtop]) {
            stack->mtop--;
        }
    }
}

int minStackTop(MinStack *stack) {
    if ((stack) && (stack->top >= 0)) {
        return stack->es[stack->top];
    }
    return INT_MAX;
}

int minStackGetMin(MinStack *stack) {
    if (stack && (stack->mtop >= 0)) {
        return stack->mes[stack->mtop];
    }
    return INT_MAX;
}

void minStackDestroy(MinStack *stack) {
    if (stack) {
        free(stack->es);
    }
}

