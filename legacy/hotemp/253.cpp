#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 扫描线算法解决会议室 II 问题。
     *
     * 核心逻辑：
     * 1. 拆解区间：[start, end] 拆成 (start, +1) 和 (end, -1)。
     * 2. 排序：按时间升序。若时间相同，-1 (散会) 排在 +1 (开会) 前面。
     * 3. 扫描：累加状态，沿途记录最大值。
     *
     * 时间复杂度: O(N log N) - 主要是排序开销
     * 空间复杂度: O(N)     - 存储边界点
     */
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<pair<int, int>> events;

        for (const auto& interval : intervals) {
            events.push_back({interval[0], 1});   // 开始
            events.push_back({interval[1], -1});  // 结束
        }

        sort(events.begin(), events.end());

        int max_rooms = 0;
        int current_rooms = 0;

        for (const auto& event : events) {
            current_rooms += event.second;
            max_rooms = max(max_rooms, current_rooms);
        }

        return max_rooms;
    }

    /**
     * @brief 使用最小堆计算最少会议室数量。
     *
     * 逻辑：
     * 1. 按照会议开始时间升序排序。
     * 2. 最小堆记录每个使用中会议室的结束时间。
     * 3. 遍历会议：若当前开始时间 >= 堆顶（最早空闲），则复用并弹出堆顶；
     *    否则必须新开会议室。无论如何，都将当前会议结束时间压入堆。
     *
     * 时间复杂度: O(N log N) - 排序及堆调整开销
     * 空间复杂度: O(N)     - 堆的最大空间
     */
    int minMeetingRoomsHeap(vector<vector<int>>& intervals) {
        if (intervals.empty())
            return 0;

        // 按开始时间升序排序
        sort(intervals.begin(), intervals.end(),
             [](const auto& a, const auto& b) { return a[0] < b[0]; });

        // 最小堆：存放每个在使用中的会议室的“结束时间”
        priority_queue<int, vector<int>, greater<int>> min_heap;

        // 初始化：放入第一个会议的结束时间
        min_heap.push(intervals[0][1]);

        for (size_t i = 1; i < intervals.size(); ++i) {
            // 如果当前会议开始时，已有会议结束，则复用该会议室
            if (intervals[i][0] >= min_heap.top()) {
                min_heap.pop();
            }
            // 压入当前会议的结束时间
            min_heap.push(intervals[i][1]);
        }

        // 堆的大小即为同时使用的最大房间数
        return min_heap.size();
    }

    /**
     * @brief 使用双指针独立排序法计算最少会议室数量。
     *
     * 逻辑：
     * 1. 分别提取所有开始时间和结束时间到两个独立数组。
     * 2. 对两个数组进行独立的升序排序（斩断原本的因果关系）。
     * 3. 双指针扫描：若开始时间 < 结束时间，说明新会议开始，房间数++；
     *    否则说明有会议结束，空出一间房，结束指针后移。
     *
     * 时间复杂度: O(N log N) - 两次独立排序
     * 空间复杂度: O(N)     - 存储开始/结束时间的数组
     */
    int minMeetingRoomsTwoPointers(vector<vector<int>>& intervals) {
        vector<int> starts, ends;
        for (const auto& itv : intervals) {
            starts.push_back(itv[0]);
            ends.push_back(itv[1]);
        }

        // 独立排序
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        int s_ptr = 0, e_ptr = 0;
        int current_rooms = 0, max_rooms = 0;

        // 开始时间遍历完，就不可能再增加房间了
        while (s_ptr < intervals.size()) {
            if (starts[s_ptr] < ends[e_ptr]) {
                // 有新会议要开始，且此时还没有会议结束
                current_rooms++;
                s_ptr++;
            } else {
                // 有会议结束了，腾出一间房
                current_rooms--;
                e_ptr++;
            }
            max_rooms = max(max_rooms, current_rooms);
        }

        return max_rooms;
    }
};