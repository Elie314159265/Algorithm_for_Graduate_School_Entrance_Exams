def bubble_sort() -> list:
    print("数字を空白区切りで入力してください")
    print("例: 3 4 2 5 1 6")
    a = list(map(int, input().split()))
    n = len(a)
    for i in range(n):
        for j in range(n - i - 1):
            if a[j] > a[j+1]:
                a[j],a[j + 1] = a[j + 1], a[j]
    print(a)
    return a
if __name__ == "__main__":
    bubble_sort()

