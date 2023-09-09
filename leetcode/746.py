class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        stair = cost[:2] + [1e9] * (len(cost) - 2)

        for i in range(2, len(cost)):
            stair[i] = min(stair[i - 1] + cost[i], stair[i])
            stair[i] = min(stair[i - 2] + cost[i], stair[i])

        return min(stair[-1], stair[-2])