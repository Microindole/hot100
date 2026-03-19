#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);

        vector<int> du(numCourses, 0);

        for (auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
            du[pre[0]]++;
        }

        int count = 0;
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (du[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int temp = q.front();
            q.pop();
            count++;

            for (int i : adj[temp]) {
                du[i]--;
                if (du[i] == 0) {
                    q.push(i);
                }
            }
        }

        return count == numCourses;
    }
};