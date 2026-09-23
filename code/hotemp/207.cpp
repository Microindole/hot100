#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int finished = 0;

        vector<int> need(numCourses, 0);
        vector<vector<int>> dep(numCourses);

        queue<int> q;

        //  { a -> b}
        for (int i = 0; i < prerequisites.size(); i++) {
            int a = prerequisites[i][0];
            int b = prerequisites[i][1];

            need[a]++;
            dep[b].push_back(a);
        }

        for (int i = 0; i < numCourses; i++) {
            if (need[i] == 0) {
                q.push(i);
                finished++;
            }
        }

        while (!q.empty()) {
            int front = q.front();
            q.pop();

            for (int i : dep[front]) {
                need[i]--;

                if (need[i] == 0) {
                    q.push(i);
                    finished++;
                }
            }
        }

        return finished == numCourses;
    }
};