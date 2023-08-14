n = int(input())
get = list(map(int, input().strip().split()))
arr = [0] * (max(get) + 1)
res = [0] * n
for i in get:
    arr[i] += 1
for i in range(len(arr) - 1):
    arr[i + 1] += arr[i]
for k in range(len(get) - 1, -1, -1):
    res[arr[get[k]] - 1] = k + 1
    arr[get[k]] -= 1
print(*res)
