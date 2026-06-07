# 二分木ノード
class Node:
    def __init__(self, key):
        self.val = key
        self.left = None
        self.right = None

# 二分探索木
# 各操作の計算量:
#   挿入・削除・探索: O(h)  h=木の高さ
#   全ての葉の高さが同じ場合: h = O(logn)
#   最悪(一直線): h = O(n)
class BinarySearchTree:
    def __init__(self):
        self.root = None


    # 挿入
    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        else:
            self._insert_recursive(self.root, key)

    def _insert_recursive(self, current_node, key):
        if key < current_node.val:
            if current_node.left is None:
                current_node.left = Node(key)
            else:
                self._insert_recursive(current_node.left, key)
        elif key > current_node.val:
            if current_node.right is None:
                current_node.right = Node(key)
            else:
                self._insert_recursive(current_node.right, key)


    # 探索
    def search(self, key):
        return self._search_recursive(self.root, key)

    def _search_recursive(self, current_node, key):
        if current_node is None or current_node.val == key:
            return current_node
        elif current_node.val > key:
            return self._search_recursive(current_node.left, key)
        else:
            return self._search_recursive(current_node.right, key)



    # 並び替え(昇順)
    def inorder(self):
        # 左 → 親 → 右 の順番で読み込むと、自然とソートされた順になる。
        result = []
        self._inorder_recursive(self.root, result)
        return result
    
    def _inorder_recursive(self, current_node, result):
        if current_node is not None:
            self._inorder_recursive(current_node.left, result)
            result.append(current_node.val)
            self._inorder_recursive(current_node.right, result)


if __name__ == "__main__":
    bst = BinarySearchTree()
    print("空白区切りでデータを入力してください。")
    print("例: 5 4 6 3 7 2 8 1")
    data_list = list(map(int, input().split()))

    for val in data_list:
        bst.insert(val)

    print(f"昇順に並び替えたデータ: {bst.inorder()}")

    print("検索したいデータを入力してください。")
    target = int(input())
    result = bst.search(target)
    if result:
        print(f"値{target}は木の中に存在します。")
    else:
        print(f"値{target}は見つかりませんでした。")
    







