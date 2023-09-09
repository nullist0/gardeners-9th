class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        answer = [0] * len(temperatures)
        cache = [1] * len(temperatures)
        stack = [(0, 0) for _ in range(len(temperatures))]
        stackp = -1
        for i in range(len(temperatures)):
            if stackp >= 0:
                count = 0
                while stack[stackp][0] < temperatures[i]:
                    index = stack[stackp][1]
                    count += cache[index]
                    answer[index] = count
                    stackp -= 1
                    if stackp == -1:
                        break
                if stackp >= 0:
                    index = stack[stackp][1]
                    cache[index] += count
            stackp += 1
            stack[stackp] = (temperatures[i], i)
        return answer