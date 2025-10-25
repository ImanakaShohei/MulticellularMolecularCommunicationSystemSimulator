# behaviorType パラメーター
ふるまいの種類を指定します。

```json
"behaviorType": {
    "type": "string",
    "enum": [
        "MoleculeAware",
        "Normal",
        "User",
        "WavePropagation"
    ]
}
```

## 型
`string`

## プロパティ
| 名前 | 説明 |
| :--- | :--- |
| `MoleculeAware` | `Normal`を継承した分子空間の影響を考慮するBehavior。 |
| `Normal` | 細胞分裂と成長を考慮するBehavior。 |
| `User` | ユーザー定義のふるまい。 |
| `WavePropagation` | 謎のふるまい。 |