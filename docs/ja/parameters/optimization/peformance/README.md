# peformance プロパティ
実行速度を優先するか、メモリ効率を優先するかを選択します。

```json
"peformance": {
    "type": "string",
    "enum": [
        "Fast",
        "LowMemory"
    ]
}
```

## 型
`string`

## プロパティ
| 名前 | 説明 |
| :--- | :--- |
| `Fast` | 速度を優先します。 |
| `LowMemory` | メモリ効率を優先します。 |

## 解説
細胞数が多いシミュレーションの場合、`LowMemory`が速くなることがあります。