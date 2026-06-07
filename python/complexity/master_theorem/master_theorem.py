import math

def master_theorem(algorithm_name: str, a, b, c) -> str:
    print(f"{algorithm_name}の計算量判定")
    print(f"漸化式: T(n) = {a}T(n/{b}) + f(n^{c})")
    log_b_a = round(math.log(a,b), 4)
    print(f"比較1 (log_b(a)) : 処理が枝分かれして増える勢い = {log_b_a}")
    print(f"比較2 (c) : 各階層での結合コストの勢い = {c}")
    
    if log_b_a > c:
        print("判定: パターン1 (log_b(a) > c) -> 分割しすぎて葉の計算量が重い")
        complexity = f"θ(n^{log_b_a})"
    elif log_b_a == c:
        print("判定: パターン2 (log_b(a) == c) -> 全階層のコストが均等")
        if c == 0:
            complexity = f"θ(logn)"
        elif c == 1:
            complexity = f"θ(nlogn)"
        else:
            complexity = f"θ(n^{c} logn)"
    else:
        print("判定: パターン3 (log_b(a) < c) -> 分割しても頂点での結合コストが重い")
        complexity = f"θ(n^{c})"
    print(f"最終的な計算量: {complexity}")
    return complexity

if __name__ == "__main__":
    print("アルゴリズムの名前、a、b、cを入力してください")
    algorithm_name = str(input())
    a, b, c = map(int, input().split())
    master_theorem(algorithm_name, a, b, c)


