def power(base: int, exp: int) -> int:
    """
    繰り返し２乗法 (2分累乗法) O(logn)
    base^exp を O(log exp) で計算する。

    base^n = (base^(n/2))^2 if n is even
    base^n = base * base^(n-1) if n is odd

    T(n) = T(n/2) + o(1) → O(logn)
    """
    if exp == 0:
        return 1
    if exp % 2 == 0:
        half = power(base, exp // 2)
        return half * half
    return base * power(base, exp - 1)

if __name__ == "__main__":
    print("繰り返し２乗法")
    print("base^n を高速に計算します。baseとn (整数)を入力してください")
    base, n = map(int, input().split())
    result = power(base, n)
    print(f"{base}^{n} = {result}")

