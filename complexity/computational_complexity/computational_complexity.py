def count_ops_O_n(n: int) -> int:
    # 線形時間 O(n)
    count = 0
    for _ in range(n):
        count += 1
    return count

def count_ops_O_n2(n: int) -> int:
    # 二重ループ O(n^2)
    count = 0
    for _ in range(n):
        for _ in range(n):
            count += 1
    return count

def count_ops_O_n_logn(n: int) -> int:
    # マージソートやヒープソートに相当する計算量 O(nlogn)
    count = 0
    for _ in range(n):
        i = 1
        while i < n:
            count += 1
            i *= 2
    return count

def count_ops_O_log_n(n: int) -> int:
    # 2分探索に相当する計算量 O(logn)
    count = 0
    i = 1
    while i < n:
        count += 1
        i = i * 2
    return count


if __name__ == "__main__":
    print("O(n), O(n^2), O(nlogn), O(logn)を実際に配列の要素数を渡してシミュレーションする")
    print("ソートする配列の要素数nを入力してください。(n > 0 の自然数)")
    n = int(input())
    print(f"O(n): {count_ops_O_n(n)}")
    print(f"O(n^2): {count_ops_O_n2(n)}")
    print(f"O(nlogn): {count_ops_O_n_logn(n)}")
    print(f"O(logn): {count_ops_O_log_n(n)}")

