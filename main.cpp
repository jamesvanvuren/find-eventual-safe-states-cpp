#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// It would be better to use the STL "foreach" algorithm with a lambda to implement this function, but at least the code is simple.
//
void printVector(const vector<int>& vec) {

    for(const int& i: vec) {

        cout << " " << i;

    }

    cout << endl;
}

// Solution to https://leetcode.com/problems/find-eventual-safe-states
//
class Solution {

private:

    // Function to do a depth-first traversal of the graph.
    //
    // One important part of the solution is that the overall traversal is not interrupted when a previously visited node (a cycle in the graph) 
    // is found, although the previously visited node itself will not be visited again. The overall traversal not being interrupted means that 
    // outbound edges from earlier nodes in the traversal (for calls higher in the call stack) will still be followed.
    // 
    // The fact that the overall traversal does not get interrupted means that all nodes reachable from the the initial node in the traversal 
    // will be visited.
    //
    // This means that when the traversal is finished, we will know whether the initial node in the traversal is "safe" or not.
    //
    // And using a cache is a form of dynamic programming, which is fun.
    //
    static bool dfs(const vector<vector<int>>& graph, std::unordered_map<int, bool>& cache, std::unordered_set<int>& unvisitedNodesSet, vector<int>& safeAndTerminalNodesVec, int node) {

        bool result = true;  // True = safe.

        // Remove the current node from the set of unvisited nodes.
        unvisitedNodesSet.erase(node);

        // Get reference to the rector of edges leading out from the current node.
        const vector<int> &edgeVec = graph[node];

        // For each outbound edge...
        for(size_t i = 0; i < edgeVec.size(); i++) {

            int destNode = edgeVec[i];

            // Check if we have a result for the destination node from a previous traversal.
            const auto& iter = cache.find(destNode);
            if (iter != cache.end()) {

                // Found entry for node in the cache. This node was visited during a traversal of a different subgraph of the overall graph.
                auto cachedResult = *iter;
                if (!cachedResult.second) {
                    result = false;
                }
            }
            else {

                // We do not have a result for the destination node from a previous traversal. Check if we have visited this node already during 
                // this traversal (which is a traversal of the subgraph of all nodes reachable from the initial node). If so, that's a cycle in
                // the current subgraph.
                if (unvisitedNodesSet.find(destNode) == unvisitedNodesSet.end()) {

                    // Found a cycle in the graph.
                    result = false;

                }
                else {
                    
                    // We do not have a result for the destination node from a previous traversal. And we have not visited this destination node
                    // during the current traversal (which is a traversal of the subgraph of all nodes reachable from the initial node). So
                    // this node still needs to be processed to see whether it is safe or not. Do recursive DFS on the dest node.
                    if (!dfs(graph, cache, unvisitedNodesSet, safeAndTerminalNodesVec, destNode)) {

                        result = false;

                    }

                }

            }

        }

        // Have finished traversing all the nodes reachable from the initial node. Cache whether the initial node was safe or not.
        cache[node] = result;

        if (result) {
            safeAndTerminalNodesVec.push_back(node);
        }

        return result;

    }

public:

    static auto eventualSafeNodes(const vector<vector<int>>& graph) {

        // After we finish, this will contain the set of nodes that are either terminal nodes, or whose outbound edges all 
        // lead to other safe or terminal nodes - see https://leetcode.com/problems/find-eventual-safe-states
        vector<int> safeAndTerminalNodesVec;

        // Use unordered_map<> to get O(1) lookup performance.
        std::unordered_map<int, bool> cache;

        // Use unordered_set<> to get O(1) lookup performance.
        std::unordered_set<int> unvisitedNodesSet;

        // Add all nodes to unvisitedNodesSet.
        for(size_t i = 0; i < graph.size(); i++) {
            unvisitedNodesSet.insert(i);
        }

        // The overall graph can consist of separate subgraphs that are unreachable from each other.
        while (!unvisitedNodesSet.empty()) {

            int unvisitedNode = *(unvisitedNodesSet.begin());

            dfs(graph, cache, unvisitedNodesSet, safeAndTerminalNodesVec, unvisitedNode);
        }

        // The problem statement says to return the list of safe nodes in numeric order.
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