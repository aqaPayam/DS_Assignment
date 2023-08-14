class Shop:
    def __init__(self, number, index):
        self.number = number
        self.index = index


def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    m = len(arr) // 2
    left = merge_sort(arr[:m])
    right = merge_sort(arr[m:])
    return merge(left, right)


def merge(left, right):
    finalArr = [0] * (len(right) + len(left))
    l = f = r = 0
    while l < len(left) or r < len(right):
        if l < len(left) and (r >= len(right) or left[l].number <= right[r].number):
            finalArr[f] = left[l]
            l += 1
        else:
            finalArr[f] = right[r]
            r += 1
        f += 1
    return finalArr


n = int(input())
list_input_numbers = list(map(int, input().split()))[:n]
numbers = [None] * n
for i in range(0, n):
    numbers[i] = Shop(list_input_numbers[i], i)
numbers = merge_sort(numbers)

sum = left = right = 0
result = [0] * n
for i in range(0, n):
    if i % 2 == 0:
        sum += right
        temp = numbers[i].number
        numbers[i].number = right
        right += temp
    else:
        sum += left
        left += numbers[i].number
        numbers[i].number = left * -1
    result[numbers[i].index] = numbers[i].number
print('{0:.7f}'.format(sum / n))
print(*result, sep=" ")
