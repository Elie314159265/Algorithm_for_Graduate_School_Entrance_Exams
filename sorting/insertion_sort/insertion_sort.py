def insertion_sort() -> list:
    print("空白区切りで数字を入力してください")
    print("例: 3 2 4 1 5")
    arr = list(map(int, input().split()))
    n = len(arr)
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

if __name__ == "__main__":
    arr = insertion_sort()
    print(arr)



