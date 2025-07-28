#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;
using pt = complex<ld>;


ll n;
ld EPS;

struct endpt {
    ll hair, other;
};

auto dot(pt a, pt b) {return real(conj(a) * b);}
pt circleRayIntersection(pt orig, pt dir) {
    pt center = {0.0, 0.0};
    ld r = 1.0;
    vector<pt> result;
    ld a = norm(dir);
    ld b = 2 * dot(dir, orig - center);
    ld c = norm(orig - center) - r * r;
    ld discr = b * b - 4 * a * c;
    ld t1 = -(b + sqrt(discr)) / (2 * a);
    ld t2 = -(b - sqrt(discr)) / (2 * a);
    if (abs(t2) > abs(t1)) swap(t1, t2);
    return t1 * dir + orig;
}

pt getPt(ll i) {
    ld angle = (ld) i / n * M_PI;
    return exp(angle * pt(0, 1));
}

ld getAngle(ll a, ll b) {
    pt p1 = getPt(a);
    pt p2 = getPt(b);
    if (arg(p1 - p2) < 0) return arg(p1 - p2) + M_PI;
    else return arg(p1 - p2);
}

ll findPartner(ld angle, ll i) {
    pt orig = getPt(i);
    pt dir = polar<ld>(1, angle);
    pt partner = circleRayIntersection(orig, dir);
    ll p = llround(arg(partner) * n / M_PI);
    return (p + 2 * n) % (2 * n);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll a, b;
    cin >> n;
    EPS = M_PI / (2.0 * n);

    vector<endpt> endp(2 * n);

    for0(i, n) {
        cin >> a >> b;
        endp[a] = {i, b};
        endp[b] = {i, a};
    }

    vl countSum(2 * n, 0);
    vector<ld> angles;
    for0(i, 2 * n) {
        if ((i + endp[i].other) % 2 == 1) angles.pb(getAngle(i, endp[i].other));
    }
    sort(angles.begin(), angles.end());
    ll count = 0;
    ld curAngle = angles[0];
    ld bestAngle;
    ll maxCount = 0;
    for0(i, sz(angles)) {
        if (abs(angles[i] - curAngle) < EPS) count++;
        else {
            if (count > maxCount) {
                maxCount = count;
                bestAngle = curAngle;
            }
            count = 1;
            curAngle = angles[i];
        }
    }
    if (count > maxCount) {
        maxCount = count;
        bestAngle = curAngle;
    }

    cout << n - maxCount / 2 << endl;
    if (maxCount == 0) bestAngle = getAngle(0, 1);

    for0(i, 2 * n) {
        if (abs(getAngle(i, endp[i].other) - bestAngle) < EPS) continue;
        ll cur = i;
        ll curBest = findPartner(bestAngle, cur);
        endp[endp[cur].other].hair = -1;
        while (endp[curBest].hair != -1) {
            cout << endp[cur].hair << " " << endp[cur].other << " " << curBest << endl;
            endp[cur].other = curBest;
            ll next = endp[curBest].other;
            endp[curBest] = {endp[cur].hair, cur};
            cur = next;
            curBest = findPartner(bestAngle, cur);
        }
        cout << endp[cur].hair << " " << endp[cur].other << " " << curBest << endl;
        endp[cur].other = curBest;
        endp[curBest] = {endp[cur].hair, cur};
    }
}