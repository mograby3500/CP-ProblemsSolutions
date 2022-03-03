#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 55;
long long cap[N][N], C[N][N];
int n, m, x;
bool vis[N];
int path[N], path_len;
long long getPath(int src, int target, int len, long long maxCapacity){
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
     long long total_flow = 0;
     while(1){
          memset(vis, 0, sizeof vis);
          long long new_flow = getPath(src, sink, 0, INT_MAX);
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
double EPS = 1e-7;
bool ok(double X){
     
     if(X == 0)
          return 1;
     
     for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
               cap[i][j] = (C[i][j]+EPS) / X;
          }
     }
     return maxFlow(0, n - 1) >= x;
}
void solveTestCase(){
     cin>>n>>m>>x;
     
     for(int i = 0; i < m; i++){
          int u, v, c;
          cin>>u>>v>>c; --u, --v;
          C[u][v] = c;
     }

     double L = 0, R = INT_MAX, ans;
     for(int itr = 0; itr < 100; itr++){
          double md = (L + R) * 0.5;
          if(ok(md)){
               ans = md;
               L = md;
          }else
               R = md;
     }
     cout<<x * ans<<"\n";
}
int main(){
     cin.tie(0);
     cin.sync_with_stdio(0);
     cout<<fixed<<setprecision(10);
     
     int T = 1;
     while(T--)
          solveTestCase();
}
