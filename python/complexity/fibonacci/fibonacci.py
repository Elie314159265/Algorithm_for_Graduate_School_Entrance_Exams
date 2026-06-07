import time

def fib_native(n: int) -> int:
    """
    単純再帰: O(2^n)
    T(n) = T(n-1) + T(n-2) + O(1)
    ≈ T(n-1) + T(n-1) = 2T(n-1) → O(2^n)
    """
    if n <= 1:
        return n
    return fib_native(n-1) + fib_native(n-2)



fib_memo_dict: dict = {}

def fib_memo(n: int) -> int:
    """
    メモ化再帰(Top Down DP) : O(n)
    各 fib(k) が1回だけ計算される
    """
    if n <= 1:
        return n
    if n in fib_memo_dict:
        return fib_memo_dict[n]
    fib_memo_dict[n] = fib_memo(n-1) + fib_memo(n-2)
    return fib_memo_dict[n]



def fib_dp(n: int) -> int:
    """
    動的計画法(Bottom-Up DP) : 計算量O(n) / 空間計算量O(1)
    """
    if n <= 1:
        return n
    prev2, prev1 = 0, 1
    for _ in range(1, n):
        curr = prev1 + prev2
        prev2, prev1 = prev1, curr
    return curr


def fib_matrix(n: int) -> int:
    """
    行列累乗法: O(logn)
    [F(n+1)] = [1 1][F(n)]
    [F(n)  ] = [1 0][F(n-1)]
    を用いる
    """
    if n <= 1:
        return n

    def mat_mul(A: list, B:list) -> list:
        return [
                [A[0][0]*B[0][0] + A[0][1]*B[1][0], A[0][0]*B[0][1] + A[0][1]*B[1][1]],
                [A[1][0]*B[0][0] + A[1][1]*B[1][0], A[1][0]*B[0][1] + A[1][1]*B[1][1]]
        ]
    def mat_pow(M: list, p: int) -> list:
        # ２分累乗法: O(logn)　回の行列計算
        if p == 1:
            return M
        if p % 2 == 0:
            half =mat_pow(M, p // 2)
            return mat_mul(half, half)
        else:
            return mat_mul(M, mat_pow(M, p - 1))

    base = [[1,1],[1,0]]
    result = mat_pow(base, n)
    return result[0][1]



def compare_fib_performance(n: int) -> None:
    start = time.perf_counter()
    result = fib_native(n)
    t_native = (time.perf_counter() - start) * 1000
    print(f"native実装の結果: {result}")
    print(f"実行時間: {t_native}ms")
    print("----------------------------")

    fib_memo_dict.clear()
    start = time.perf_counter()
    result = fib_memo(n)
    t_memo = (time.perf_counter() - start) * 1000
    print(f"memo実装の結果: {result}")
    print(f"実行時間: {t_memo}ms")
    print("----------------------------")

    start = time.perf_counter()
    result = fib_dp(n)
    t_dp = (time.perf_counter() - start) * 1000
    print(f"dp実装の結果: {result}")
    print(f"実行時間: {t_dp}ms")
    print("----------------------------")
    
    start = time.perf_counter()
    result = fib_matrix(n)
    t_matrix = (time.perf_counter() - start) * 1000
    print(f"matrix実装の結果: {result}")
    print(f"実行時間: {t_matrix}ms")
    print("----------------------------")


if __name__ == "__main__":
    print("フィボナッチ数列の各実装の実行時間を比較します")
    print("自然数nを入力してください")
    n = int(input())
    compare_fib_performance(n)
