def find_number_of_way_to_build(n):
    mx = 0
    cnt = 0
    a = 1
    b = 2
    bbb = 8
    while a * bbb <= n:
        a = n // bbb
        cnt += a
        mx = max(mx, a * bbb)
        b += 1
        a = 1
        bbb = b * b * b
    return cnt, mx


target = int(input())
first = 8
last = 8 * target
while first <= last:
    mid = (first + last) // 2
    midSolve, answer = find_number_of_way_to_build(mid)
    if midSolve == target:
        print(answer)
        exit()
    elif midSolve > target:
        last = mid - 1
    else:
        first = mid + 1
print(-1)
