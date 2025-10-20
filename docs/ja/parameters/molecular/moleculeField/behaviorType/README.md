# behaviorType パラメーター
分子空間のふるまいの種類を選択します

```json
"behaviorType": {
    "type": "string",
    "enum": [
        "Normal",
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
| `Normal` | 通常の分子拡散。 |
| `Null` | 何もしないBehavior。 |
| `User` | ユーザー定義のふるまい。 |