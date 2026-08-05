class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {

        vector<vector<int>> adj(n);
        for(auto x : invocations){
            adj [x[0]].push_back(x[1]);
        }

        vector<int>vis(n,0);
        function<void(int)>dfs = [&](int node){
            vis[node] = 1;
            for (int next : adj[node]){
                if (!vis[next])
                    dfs(next);
            }
        };

        dfs(k);

        for (auto x : invocations){
            if (!vis[x[0]]&& vis[x[1]]){
                vector<int> ans;
                for(int i = 0 ; i < n ; i++)
                ans.push_back(i);
                return ans;
            }
        }
        vector<int>ans;
        for(int i = 0 ; i<n ; i++){
            if(!vis[i])
                ans.push_back(i);
        }
        return ans;
        
    }
};