class Unionfind{
public:
    vector<int> parent;
    vector<int> rank;
    Unionfind(int n){
        parent.resize(n);
        rank.resize(n,1);
        for(int i=0; i<n; i++){
            parent[i]=i;
        }
    }

    int find_parent(int x){
        if(parent[x]==x) return x;
        parent[x]=find_parent(parent[x]);
        return parent[x];
    }

    void unite(int x, int y){
        int px = find_parent(x);
        int py = find_parent(y);

        if(rank[px]>rank[py]){
            parent[py]=px;
        }
        else if(rank[py]>rank[px]){
            parent[px]=py;
        }
        else{
            parent[py]=px;
            rank[px]++;
        }
    }
};


class Solution {
public:

    int GetMst(int n, vector<vector<int>> edges, int excludeEdge=-1, int includeEdge=-1){
        Unionfind uf(n);
        int count=0;
        int weight=0;

        if(includeEdge!=-1){
            uf.unite(edges[includeEdge][0], edges[includeEdge][1]);
            weight += edges[includeEdge][2];
            count++;
        }

        for(int i=0; i<edges.size(); i++){
            if(i==excludeEdge) continue;

            int px = uf.find_parent(edges[i][0]);
            int py = uf.find_parent(edges[i][1]);
            int w = edges[i][2];

            if(px!=py){
                uf.unite(px, py);
                weight+=w;
                count++;
            }
        }
        
        if(count==n-1) return weight;
        return INT_MAX;

    }


    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {

        vector<vector<int>> edgesWithIndex;
        int index=0;
        for(auto& j: edges){
            edgesWithIndex.push_back({j[0] , j[1], j[2] , index});
            index++;
        }

        sort(edgesWithIndex.begin(), edgesWithIndex.end(),[](const vector<int>&a , vector<int>&b){
            return a[2]<b[2];
        });

        int original_mst_weight = GetMst(n, edgesWithIndex);

        vector<vector<int>> ans(2);
        for(int i=0; i<edges.size(); i++){
            if(GetMst(n, edgesWithIndex, i) > original_mst_weight){
                ans[0].push_back(edgesWithIndex[i][3]);
            }
            else if(GetMst(n, edgesWithIndex, -1, i) == original_mst_weight){
                ans[1].push_back(edgesWithIndex[i][3]);
            }
        }
        return ans;
    }
};