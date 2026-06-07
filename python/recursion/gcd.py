def gcd(a: int, b: int) -> int:
    """
    ユークリッドの互除法 O(log(min(a,b)))
    gcd(a,b) = gcd(b, a mod b) (b > 0)
    """
    if b == 0:
        return a
    return gcd(b, a % b)

if __name__ == "__main__":
    print("a,b (a>b) の最大公約数をユークリッドの互除法で求めます。")
    print("a,bを入力してください。")
    a, b = map(int, input().split())
    result = gcd(a,b)
    print(f"{a}と{b}の最大公約数は{result}")

