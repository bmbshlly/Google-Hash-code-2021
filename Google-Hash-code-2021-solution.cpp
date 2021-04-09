#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
typedef tree<long long,null_type,less_equal<long long>,rb_tree_tag,tree_order_statistics_node_update> indexed_multiset;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<string> vs;
typedef priority_queue<int> pqmaxi;
typedef priority_queue<ll> pqmaxl;
typedef priority_queue<int, vi, greater<int>> pqmini;
typedef priority_queue<ll, vl, greater<ll>> pqminl;

// A hash function used to hash a pair of any kind 
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

// vl => vector<long long>
struct VectorHasher {
    ll operator()(const vl &V) const {
        ll hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

template <typename T,typename U> using umap=unordered_map<T,U>;
template <typename T>            using uset=unordered_set<T>;

#define F first;
#define S second;
#define fo(i, a, b) for (long long i = a; i < b; ++i)
#define fm(i, a, b) for (long long i = a; i > b; --i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define test     \
    ll test;     \
    cin >> test; \
    while (test--)
#define pb(i) push_back(i)
#define eb(i) emplace_back(i)
#define mp(i, j) make_pair(i, j)
#define fast                     \
    ios::sync_with_stdio(false); \
    cin.tie(NULL);
const ll mod  = 1000000007;
const ll mod2 = 998244353;

// --------- IMP FUNCTIONS----------------------------------------------------------------------------------------------------------------

// Binary Exponentiation under mod p
ll power(ll x,ull y,ll p){ 
    ll r=1;  x%=p;
    if(!x) return 0;  
    while(y){    
        if(y&1) r=(r*x)%p;    
        y>>=1;   
        x=(x*x)%p;  
    }  
    return r;  
}

// String multiplication
string operator*(string lhs, const int rhs){
    string res="";
    for(int i=0;i<rhs;++i) res+=lhs;
    return res;
}

//-----CODE-----------------------------------------------------------------------------------------------------------------------
struct street{
    ll start, end, time;
};

int main(){
    auto time_req= clock();
    fast;
    // code goes here

    ll duration, intersections, streets, cars, score; cin >> duration >> intersections >> streets >> cars >> score;

    map<ll,ll> visitedIntersection; // intersection : no of times 
    map<string,ll> visitedStreet;
    vector<vector<string>> graph(intersections); // incoming
    // vectorI<string>
    map<string,street> streetMap;
    
    fo(i,0,streets){
        // ith street
        street x; string name;
        cin >> x.start >> x.end >> name >> x.time;
        graph[x.end].pb(name);
        streetMap[name]=x;
        // cout << i << "th street from " << x.start << " to " << x.end << " with name " << x.name << " time length of " << x.time << "\n";
    }

    vector< pair<ll,vector<string>> > carList;

    fo(i,0,cars){
    // ith car
        ll numberOfStreets; cin >> numberOfStreets;
        ll cost = 0 ;
        vector<string> streetfighter;
        fo(j,0,numberOfStreets){
            string Stname;
            cin >> Stname;
            streetfighter.pb(Stname);
            if(j) cost+=streetMap[Stname].time;
        }
        if(cost<=duration) carList.push_back(mp(cost,streetfighter));
        streetfighter.clear();
    }
    sort(all(carList));
    ll a = round((float)sz(carList)*1);   
    // cout << "no of cars : " << a << "\n";
    fo(idx,0,a){
        auto v = carList[idx].second;
        ll numberOfStreets = sz(v);
        fo(j,0,numberOfStreets){
            string Stname = v[j];
            if(j!=numberOfStreets-1){
                visitedIntersection[streetMap[Stname].end]++;
                visitedStreet[Stname]++;
            }
        }
    }

    ll count=0;
    for(auto i: visitedIntersection) if(i.second) count++;
    cout << count << "\n";

    for(auto i: visitedIntersection) if(i.second){
        cout << i.first << "\n";
        ll cnt=0;
        for(auto name: graph[i.first]) if(visitedStreet[name]) cnt++;
        cout << cnt << "\n";
        for(auto name: graph[i.first]) {
            if(visitedStreet[name]) {
                ll ans = visitedStreet[name]/sz(graph[i.first]);
                if(!ans) ans++;
                cout << name << " " << ans << "\n";
            }
        }
    }

    cerr << "\nSolved, time = " << (float)(clock()-time_req)/CLOCKS_PER_SEC << "s\n";
    return 0;
}
