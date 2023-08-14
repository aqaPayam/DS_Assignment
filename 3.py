def binary_insert(arr, k, maxxx):
    f = 0
    l = len(arr)
    while f <= l:
        mid = (f + l) // 2
        if arr[mid] > k:
            l = mid - 1
        else:
            f = mid + 1
    return arr[:f] + [k] + arr[f:]


def find_max(arr, maxxx):
    maxx = 0
    for j in range(len(arr) - 1):
        if arr[j + 1] - arr[j] > maxx:
            maxx = arr[j + 1] - arr[j]
            maxxx[0] = arr[j]
            maxxx[1] = arr[j + 1]


n, q = input().split()
arr = list(map(int, input().split()))
n = int(n)
q = int(q)
res = [0, n]
maxxx = [0, n]
for i in range(q):
    tmp = arr[i]
    res = binary_insert(res, tmp, maxxx)
    if maxxx[0] < tmp < maxxx[1]:
        find_max(res, maxxx)
    print(maxxx[1] - maxxx[0])
