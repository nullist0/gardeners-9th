def is_sayable(string, words):
    for word in words:
        string = string.replace(word, "|", 1)
    string = string.replace("|", "")
    return len(string) == 0

def solution(babbling):
    answer = 0
    words = ["aya", "ye", "ma", "woo"]
    for string in babbling:
        if is_sayable(string, words):
            answer += 1
    return answer