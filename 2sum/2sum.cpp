#include <iostream>
#include <vector>
#include <stdlib.h>

using std::vector;
using std::cin;
using std::cout;

class Solution {
public:
    Solution() {}
    virtual ~Solution() {}

    int hashValue(int arg, int target)
    {
        int t = arg + arg - target;
        return t < 0 ? (-t) : t;
    }
    
    vector<int> twoSum(vector<int>& nums, int target)
    {
        int max;
        vector<int> ret;
        vector<int> nn(nums.size());
        int t;
        int max_abs = 0;
        for (int i = 0; i < nn.size(); i++) {
            nn[i] = t = (nums[i] << 1) - target;
            if (t < 0) {
                t = -t;
            }
            if (t > max_abs) {
                max_abs = t;
            }
        }
        vector<int> ht(max_abs + 1);
        for (int i = 0; i <= max_abs; i++) {
            ht[i] = -1;
        }
        for (int i = 0; i < nn.size(); i++) {
            t = nn[i];
            if (t < 0) {
                t = -t;
            }
            if (ht[t] >= 0) {
                if (nn[i] + nn[ht[t]] == 0) {
                    ret.push_back(ht[t] + 1);
                    ret.push_back(i + 1);
                    return ret;
                }
            }
            ht[t] = i;
        }
        return ret;
    }
};

int main (int argc, char** argv)
{
    int target = ::strtol(argv[1], NULL, 0);

    vector<int> v;
    for (int i = 2; i < argc; i++) {
        v.push_back(::strtol(argv[i], NULL, 0));
    }
    Solution sol;
    vector<int> ret;
    ret = sol.twoSum(v, target);
    if (ret.size() == 2) {
        std::cout << "index1=" << ret[0] << ", index2=" << ret[1] << "\n";
    }
    return 0;
}
