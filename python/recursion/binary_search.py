def binary_search(arr: list, target: int, lo: int = 0, hi: int = None) -> int:
    if hi is None:
        hi = len(arr) - 1
    
    if lo > hi:
        return -1
    
    mid = (lo + hi) // 2

    if arr[mid] == target:
        return mid
    elif arr[mid] < target:
        return binary_search(arr, target, mid + 1, hi)
    else:
        return binary_search(arr, target, lo, mid - 1)

if __name__ == "__main__":
    print("整列済みの配列から目的の数を二分探索で探索します。")
    print("配列と探索する数を入力してください。")
    print("配列を入力(例: 2 3 5 6 7 9)")
    arr = list(map(int, input().split()))
    print("探索する数を入力してください")
    target = int(input())
    result = binary_search(arr, target)
    if result != -1:
        print(f"目的の数は配列の{result}番目に存在します")
    else:
        print("目的の数は配列の中に存在しません。")

