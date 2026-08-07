#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Factors {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
    };

    bool getFactors(long long t, Factors& f) {
        while (t % 2 == 0) { f.c2++; t /= 2; }
        while (t % 3 == 0) { f.c3++; t /= 3; }
        while (t % 5 == 0) { f.c5++; t /= 5; }
        while (t % 7 == 0) { f.c7++; t /= 7; }
        return t == 1;
    }

    inline int minLengthNeeded(const Factors& req) {
        int count = max(0, req.c7) + max(0, req.c5);
        int c2 = max(0, req.c2);
        int c3 = max(0, req.c3);

        int c9 = c3 / 2;
        c3 %= 2;

        int c8 = c2 / 3;
        c2 %= 3;

        int c6 = 0;
        if (c2 == 1 && c3 == 1) {
            c2 = 0; c3 = 0; c6 = 1;
        } else if (c2 == 2 && c3 == 1) {
            c2 = 1; c3 = 0; c6 = 1;
        }

        int c4 = c2 / 2;
        c2 %= 2;

        return count + c9 + c8 + c6 + c4 + c2 + c3;
    }

    inline void applyDigit(Factors& f, int d, int sign) {
        if (d == 2) f.c2 -= sign * 1;
        else if (d == 3) f.c3 -= sign * 1;
        else if (d == 4) f.c2 -= sign * 2;
        else if (d == 5) f.c5 -= sign * 1;
        else if (d == 6) { f.c2 -= sign * 1; f.c3 -= sign * 1; }
        else if (d == 7) f.c7 -= sign * 1;
        else if (d == 8) f.c2 -= sign * 3;
        else if (d == 9) f.c3 -= sign * 2;
    }

    string fillSuffix(int len, Factors req) {
        string res = "";
        res.reserve(len);
        for (int position = 0; position < len; ++position) {
            int remLen = len - 1 - position;
            for (int d = 1; d <= 9; ++d) {
                Factors nextReq = req;
                applyDigit(nextReq, d, 1);

                if (minLengthNeeded(nextReq) <= remLen) {
                    res += (char)('0' + d);
                    req = nextReq;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        Factors targetReq;
        if (!getFactors(t, targetReq)) return "-1";

        int n = num.size();
        
        vector<Factors> pref(n + 1);
        pref[0] = targetReq;
        
        int limit = n;
        for (int i = 0; i < n; ++i) {
            if (num[i] == '0') {
                limit = i;
                break;
            }
            pref[i + 1] = pref[i];
            applyDigit(pref[i + 1], num[i] - '0', 1);
        }

        if (limit == n && minLengthNeeded(pref[n]) <= 0) {
            return num;
        }

        for (int i = limit; i >= 0; --i) {
            int startDigit = (i < n) ? (num[i] - '0' + 1) : 1;
            
            for (int d = startDigit; d <= 9; ++d) {
                Factors nextReq = pref[i];
                applyDigit(nextReq, d, 1);

                int remLen = n - 1 - i;
                if (minLengthNeeded(nextReq) <= remLen) {
                    string ans = num.substr(0, i);
                    ans += (char)('0' + d);
                    ans += fillSuffix(remLen, nextReq);
                    return ans;
                }
            }
        }

        int minLen = max(n + 1, minLengthNeeded(targetReq));
        return fillSuffix(minLen, targetReq);
    }
};