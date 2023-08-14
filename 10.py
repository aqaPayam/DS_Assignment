from copy import deepcopy


def find(arr, i, j, str, c, n, m):
    if c >= len(str):
        return True
    if i < 0 or i >= n or j < 0 or j >= m:
        return False
    if arr[i][j] == str[c]:
        arr[i][j] = None
        res = (find(arr, i - 1, j, str, c + 1, n, m)
               or find(arr, i + 1, j, str, c + 1, n, m)
               or find(arr, i, j - 1, str, c + 1, n, m)
               or find(arr, i, j + 1, str, c + 1, n, m))
        arr[i][j] = str[c]
        return res
    return False


tmp = list(map(int, input().split()))
n, m = tmp[0], tmp[1]
arr = [[None] * m] * n
places = {}
for i in range(n):
    tmp = [*input()]
    for j in range(len(tmp)):
        if places.get(tmp[j]) is None:
            places[tmp[j]] = [[i, j]]
        else:
            places[tmp[j]] += [[i, j]]
    arr[i] = tmp

a = int(input())
for k in range(a):
    str = input()
    if places.get(str[0]) is not None:
        for place in places.get(str[0]):
            if find(arr, place[0], place[1], str, 0, n, m):
                print(str)
                break
