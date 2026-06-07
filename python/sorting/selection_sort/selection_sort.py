def selection_sort() -> list:
    print("空白区切りで0以上の数字の入力してください")
    print("例: 2 4 3 6 5")
    arr = list(map(int, input().split()))
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[min_idx] > arr[j]:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i] 
    return arr

if __name__ == "__main__":
    arr = selection_sort()
    print(arr)



