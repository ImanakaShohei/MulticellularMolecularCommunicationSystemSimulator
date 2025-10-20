# algorithmType パラメーター
使用する最適化アルゴリズムの種類を選択します。

```json
"algorithmType": {
    "type": "string",
    "enum": [
        "BarnesHut",
        "CellList",
        "Naive",
        "Null",
        "User"
    ]
}
```

## 型
`string`

## プロパティ
| 名前 | 説明 |
| :--- | :--- |
| `BarnesHut` | Barnes-Hutアルゴリズム。 |
| `CellList` | CellList。 |
| `Naive` | ナイーブなアルゴリズム。 |
| `Null` | 何もしないアルゴリズム。 |
| `User` | ユーザー定義のアルゴリズム。 |

## 解説
アルゴリズムによっては、独自のパラメーターの設定が必要なことがあります。