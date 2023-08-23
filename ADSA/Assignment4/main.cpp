#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parent;
vector<pair<int,pair<int,int>>> build_edges, destroy_edges;
int totalCost = 0;

int find(int x){
    while (parent[x] != -1){
        x = parent[x];
    }
    return x;
}
bool _union(int x, int y){
    int x_root = find(x);
    int y_root = find(y);
    if (x_root == y_root){
    return false;
    }else {
        parent[x_root] = y_root;
        return true;
    }
}

vector <vector <int>> store_vector(string s){
    vector <vector <int>> graph;
    vector <int> row;
    for (unsigned i=0; i<s.length(); ++i){
        char c = s.at(i);
        if (c != ','){
            if (c >= '0' && c<= '9'){
            row.push_back(c-'0');

            }else if (c >= 'a' && c<= 'z'){
            row.push_back(c-'a' + 26);

            }else if (c >= 'A' && c<= 'Z'){
            row.push_back(c-'A');
            }

        }else {
            graph.push_back(row);
            row.clear();
        }
    }
     graph.push_back(row);
     row.clear();
     return graph;
}


int main(){
    string countryAt;
    string buildAt;
    string destroyAt;

    cin>> countryAt >> buildAt >> destroyAt;

    vector <vector <int>> country = store_vector(countryAt);

    vector <vector <int>> build_cost = store_vector(buildAt);

    vector <vector <int>> destroy_cost = store_vector(destroyAt);

    for (unsigned int i= 0; i < country.size(); i++) {
        for (unsigned int j = 0; j < i; j++) {
          if (country[i][j] != 1){
                build_edges.push_back({build_cost[i][j], {i,j}});
            }else{
                destroy_edges.push_back({destroy_cost[i][j], {i,j}});
            }
        }
    }

    // sort build cost in increasing order
    sort(build_edges.begin(),build_edges.end());
    // sort destroy cost in decreasing order
    sort(destroy_edges.rbegin(), destroy_edges.rend());

    // 初始化 parent
    int num = countryAt.find(',');
    for (int i = 0; i < num; ++i) {
        parent.push_back(-1);
    }

    for (unsigned int i = 0; i < country.size(); i++) {
        for (unsigned int j = 0; j < i; j++) {
            if (country[i][j] == 1){
            _union(i,j);
        }
    }
    }

    for (unsigned int i = 0; i < build_edges.size(); ++i) {
        int cost = build_edges[i].first;
        int v1 = build_edges[i].second.first;
        int v2 = build_edges[i].second.second;
        if (_union(v1,v2)) {
            totalCost += cost;
            build_edges.push_back({0,{v1,v2}});
        }
    }

    for (unsigned int i = 0; i < parent.size(); ++i) {
        parent[i] = -1;
    }

    int tempCost = 0;
    int allCost = 0;
    for (unsigned int i = 0; i < destroy_edges.size(); ++i) {
        int cost = destroy_edges[i].first;
        allCost += cost;
        int v1 = destroy_edges[i].second.first;
        int v2 = destroy_edges[i].second.second;
        if (_union(v1,v2)) {
            tempCost += cost;
        }

    }
    totalCost = totalCost + allCost - tempCost;

    cout << to_string(totalCost) << endl;

    return 0;
}
