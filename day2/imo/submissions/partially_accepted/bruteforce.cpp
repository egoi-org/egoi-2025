#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>
typedef long long ll;
typedef long double ld;
using namespace std;

struct girl
{
    int id, sum;
    vector<int> scores;
    void init(int m, int ID)
    {
        sum = 0, id = ID;
        scores.assign(m, 0);
        for (int i = 0; i < m; i++) cin >> scores[i], sum += scores[i];
        //sort(scores.begin(), scores.end());
    }
};
bool cmp(girl a, girl b)
{
    if (a.sum == b.sum) return a.id < b.id;
    return a.sum > b.sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<girl> g(n);
    for (int i = 0; i < n; i++)
    {
        g[i].init(m, i);
    }
    sort(g.begin(), g.end(), cmp);
    int ans = n * m; // min no. of scores we need to release
    for (int mi = 0; mi < (1 << (n * m)); mi++)
    {
        bool okay = true;
        int cnt = 0;
        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mi & (1 << (i * m + j)))
                {
                    l[i] += g[i].scores[j];
                    r[i] += g[i].scores[j];
                    cnt++;
                }
                else
                {
                    r[i] += k;
                }
            }
            if (!i || l[i - 1] > r[i] || (l[i - 1] == r[i] && g[i - 1].id < g[i].id)) continue;
            okay = false;
        }
        if (okay)
        {
            ans = min(ans, cnt);
            /*if (cnt == 20)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        if (mi & (1 << (i * m + j)))
                        {
                            cout << g[i].scores[j] << " ";
                        }
                        else cout << "? ";
                    }
                    cout << " : " << l[i] << " " << r[i] << "\n";
                }
                return 0;
            }*/
        }
    }
    cout << ans << "\n";
    return 0;
}

