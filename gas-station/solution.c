//0ms version
int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    //if (!gas || !cost || (gasSize <= 0) || (gasSize != costSize)) return -1;
    int subTotal, total;
    int delta;
    int i, start = 0;
    subTotal = total = 0;
    for (i = 0; i < gasSize; i++) {
        delta = gas[i] - cost[i];
        subTotal += delta;
        if (subTotal < 0) {
            total += subTotal;
            start = i + 1;
            subTotal = 0;
        }
        total += delta;
    }
    total += subTotal;
    return (total >= 0) ? start : -1;
}
