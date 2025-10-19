# CellAlgorithm::FromType(CellAlgorithmType) 関数
[`CellAlgorithmType`](../CellAlgorithmType/README.md)からインスタンスを作成します。

```c++
[[nodiscard]]
static CellAlgorithm* FromType(
    CellAlgorithmType type
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `type` | [`CellAlgorithmType`](../CellAlgorithmType/README.md) | アルゴリズムの種類 |

## 戻り値
[`CellAlgorithm*`](../README.md)<br>
`new`でヒープに確保されたインスタンスへのポインター

## 解説
戻り値は`new`によって初期化されたインスタンスです。
領域は後でユーザー自身で`delete`によって解放する必要があります。