def quick_sort(arr) -> list:
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]

    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]

    return quick_sort(left) + middle + quick_sort(right)

if __name__ == "__main__":
    print("空白区切りで数字を入力してください")
    print("例: 3 2 4 5 1 ")
    arr = list(map(int, input().split()))
    result = quick_sort(arr)
    print(result)

