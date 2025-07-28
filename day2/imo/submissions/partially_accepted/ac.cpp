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
    vector<vector<int> > dp; // dp[number of scores revealed][sum]
    void init(int m, int k, int ID)
    {
        sum = 0, id = ID;
        scores.assign(m, 0);
        for (int i = 0; i < m; i++) cin >> scores[i], sum += scores[i];
        //sort(scores.begin(), scores.end());
        dp.assign(m + 1, vector<int>((m + 1) * (k + 1), 0));
        dp[0][sum] = 1;
        for (int i = 0; i < m; i++) for (int h = i; h >= 0; h--)
        {
            for (int s = scores[i]; s < dp[h].size(); s++)
            {
                if (!dp[h][s]) continue;
                // we will not reveal problem i
                dp[h + 1][s - scores[i]] = 1;
            }
        }
    }
};

bool cmp(girl a, girl b)
{
    if (a.sum == b.sum) return a.id < b.id;
    return a.sum > b.sum;
}

void upd(int& a, int b)
{
    a = max(a, b);
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
        g[i].init(m, k, i);
    }
    sort(g.begin(), g.end(), cmp);
    vector<vector<int> > dp(n, vector<int>(m + 1, -1));
    for (int h = 0; h <= m; h++) for (int l = 0; l + h * k <= m * k; l++) if (g[0].dp[h][l])
    {
        upd(dp[0][h], l);
    }
    for (int i = 0; i + 1 < n; i++) for (int h = 0; h <= m; h++) if (dp[i][h] != -1)
    {
        for (int hi = 0; h + hi <= m; hi++) for (int li = 0; li + hi * k <= dp[i][h]; li++)
        {
            if (li + hi * k == dp[i][h] && g[i].id > g[i + 1].id) continue;
            upd(dp[i + 1][h + hi], li);
        }
    }
    for (int hi = m; hi >= 0; hi--) if (dp[n - 1][hi] != -1)
    {
        cout << (m * n - hi) << "\n";
        return 0;
    }
    return 0;
}

