//20ms version
static int nums[128];
static int numsInited = 0;
int romanToInt(char* s) {
    if (!numsInited) {
        nums['I'] = 1;
        nums['V'] = 5;
        nums['X'] = 10;
        nums['L'] = 50;
        nums['C'] = 100;
        nums['D'] = 500;
        nums['M'] = 1000;
        numsInited = 1;
    }
    int ret = 0;
    int ch;
    while ((ch = *s++)) {
        if (*s && (nums[ch] < nums[*s])) {
            ret -= nums[ch];
        } else {
            ret += nums[ch];
        }
    }
    return ret;
}
