#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;




void printVector(const vector<int>& vec) {

    for(const int& i: vec) {

        cout << " " << i;

    }

    cout << endl;
}


void printSet(const unordered_set<int>& set) {

    for(const int& i: set) {

        cout << " " << i;

    }

    cout << endl;
}


void printGraph(const vector<vector<int>>& graph) {

    for(size_t nodeIndex = 0; nodeIndex < graph.size(); nodeIndex++) {

        const vector<int>& edgeVec = graph[nodeIndex];

        printVector(edgeVec);

    }

}


class Solution {

private:

    static bool dfs(const vector<vector<int>>& graph, std::unordered_map<int, bool>& cache, std::unordered_set<int>& unvisitedNodesSet, vector<int>& safeAndTerminalNodesVec, int node) {

        bool result = true;  // True = safe.

        unvisitedNodesSet.erase(node);

        const vector<int> &edgeVec = graph[node];

        for(size_t i = 0; i < edgeVec.size(); i++) {

            int destNode = edgeVec[i];

            const auto& iter = cache.find(destNode);
            if (iter != cache.end()) {

                // Found entry for node in the cache.
                auto cachedResult = *iter;
                if (!cachedResult.second) {
                    result = false;
                }
            }
            else {

                if (unvisitedNodesSet.find(destNode) == unvisitedNodesSet.end()) {

                    // Found a cycle in the graph.
                    result = false;

                }
                else {
                    
                    if (!dfs(graph, cache, unvisitedNodesSet, safeAndTerminalNodesVec, destNode)) {

                        result = false;

                    }

                }

            }

        }

        cache[node] = result;

        if (result) {
            safeAndTerminalNodesVec.push_back(node);
        }

        return result;

    }

public:

    static auto eventualSafeNodes(const vector<vector<int>>& graph) {

        vector<int> safeAndTerminalNodesVec;

        std::unordered_map<int, bool> cache;

        std::unordered_set<int> unvisitedNodesSet;

        // Add all nodes to unvisitedNodesSet.
        for(size_t i = 0; i < graph.size(); i++) {
            unvisitedNodesSet.insert(i);
        }

        while (!unvisitedNodesSet.empty()) {

            int unvisitedNode = *(unvisitedNodesSet.begin());

            dfs(graph, cache, unvisitedNodesSet, safeAndTerminalNodesVec, unvisitedNode);
        }

        std::sort(safeAndTerminalNodesVec.begin(), safeAndTerminalNodesVec.end());

        return safeAndTerminalNodesVec;
        
    }

};


void testCase1() {

    vector<int> node0 { 1, 2 };
    vector<int> node1 { 2, 3 };
    vector<int> node2 { 5 };
    vector<int> node3 { 0 };
    vector<int> node4 { 5 };
    vector<int> node5 {   };
    vector<int> node6 {   };

    vector<vector<int>> graph1 { node0, node1, node2, node3, node4, node5, node6 };

    auto ret = Solution::eventualSafeNodes(graph1);

    printVector(ret);
}


void testCase2() {

    vector<int> node0 { };
    vector<int> node1 { 0, 2, 3, 4 };
    vector<int> node2 { 3 };
    vector<int> node3 { 4 };
    vector<int> node4 { };

    vector<vector<int>> graph1 { node0, node1, node2, node3, node4 };

    auto ret = Solution::eventualSafeNodes(graph1);

    printVector(ret);
}


void testCase3() {

    vector<int> node0 { 1, 2 };
    vector<int> node1 { 2, 3 };
    vector<int> node2 { };
    vector<int> node3 { 5 };
    vector<int> node4 { 0 };
    vector<int> node5 { };
    vector<int> node6 { };

    vector<vector<int>> graph1 { node0, node1, node2, node3, node4, node5, node6 };

    auto ret = Solution::eventualSafeNodes(graph1);

    printVector(ret);
}


void testCase4() {

    vector<int> node0 { 1, 2 };
    vector<int> node1 { 2, 3 };
    vector<int> node2 { 5 };
    vector<int> node3 { 0, 4 };
    vector<int> node4 { 5 };
    vector<int> node5 { 0 };
    vector<int> node6 { };

    vector<vector<int>> graph1 { node0, node1, node2, node3, node4, node5, node6 };

    auto ret = Solution::eventualSafeNodes(graph1);

    printVector(ret);
}


int main() {

    testCase1();
    testCase2();
    testCase3();
    testCase4();
    
    return 0;
}