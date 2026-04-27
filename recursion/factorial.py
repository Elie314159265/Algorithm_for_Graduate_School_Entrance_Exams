def factorial(n: int) -> int:
    """
    n! の再帰計算 O(n)
    T(n) = T(n-1) + O(1) → O(n)
    """

    if n == 0:
        return 1
    return n * factorial(n-1)

if __name__ == "__main__":
    print("n!を再帰計算します。nを入力してください。")
    n = int(input())
    result = factorial(n)
    print(f"{n}! = {result}")

