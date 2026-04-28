# 九州大学システム情報科学府院試(アルゴリズム)対策Repository

## ディレクトリ構造
```
/
|---sorting/    # ソート系
|
|---complexity_analysis/   # 計算量解析
|
|---recursion_divide_conquer/   # 再帰・分割統治法
|
|---tree/   # 木構造
|
|---graph/   # グラフ
|
|---data_structures/   # データ構造
```


## 実行方法
```bash
$ python3 file.py
```

## 計算量早見表

このプロジェクトではアルゴリズムの効率をビッグ・オー記法で表現する。  
特に指定がない限りO(f(n))は最悪計算量を表す。  
 
| アルゴリズム | 最良 | 平均 | 最悪 | 空間 |
|-------------|------|------|------|------|
| バブルソート | O(n) | O(n²) | O(n²) | O(1) |
| 選択ソート | O(n²) | O(n²) | O(n²) | O(1) |
| 挿入ソート | O(n) | O(n²) | O(n²) | O(1) |
| マージソート | O(n log n) | O(n log n) | O(n log n) | O(n) |
| クイックソート | O(n log n) | O(n log n) | O(n²) | O(log n) |
| ヒープソート | O(n log n) | O(n log n) | O(n log n) | O(1) |
| BFS | — | — | O(V+E) | O(V) |
| DFS | — | — | O(V+E) | O(V) |
