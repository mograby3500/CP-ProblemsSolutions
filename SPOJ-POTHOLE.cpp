#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 250;
int cap[N][N];
int n;
int in(int node){
     return node;
}
int out(int node){
     return node + n;
}
bool vis[N];
int path[N], path_len;
int getPath(int src, int target, int len, int maxCapacity){
     path[len] = src;
     vis[src] = 1;
     if(src == target){
          path_len = len + 1;
          return maxCapacity;
     }
     int ret = 0;
     for(int i = 0; i < n; i++){
          if(vis[i] || cap[src][i] <= 0)
               continue;
          ret = getPath(i, target, len + 1,
                        min(maxCapacity, cap[src][i]));
          
          if(ret) break;
     }
     return ret;
}
int maxFlow(int src, int sink){
     int total_flow = 0;
     while(1){
          memset(vis, 0, sizeof vis);
          int new_flow = getPath(src, sink, 0, INT_MAX);
          if(new_flow == 0) break;
          for(int i = 1; i < path_len; i++){
               int u = path[i - 1], v = path[i];
               cap[u][v] -= new_flow;
               cap[v][u] += new_flow;
          }
          total_flow += new_flow;
     }
     return total_flow;
}

void solveTestCase(){
     memset(cap, 0, sizeof cap);
     cin>>n;
     for(int i = 0; i < n - 1; i++){
          int sz; cin>>sz;
          for(int j = 0; j < sz; j++){
               int to; cin>>to; --to;
               if(i == 0 || to == n - 1)
                    cap[i][to] = 1;
               else
                    cap[i][to] = INT_MAX;
          }
     }
     cout<<maxFlow(0, n - 1)<<"\n";
}
int main(){
     cin.tie(0);
     cin.sync_with_stdio(0);
     
     int T; cin>>T;
     while(T--)
          solveTestCase();
}
