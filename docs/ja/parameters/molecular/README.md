# molecular パラメーター
分子空間を設定します。

```json
"molecular": {
    "type": "array",
    "items": {
        "$ref": "#/$defs/moleculeField"
    }
},
```

## 要素型
| 名前 | 説明 |
| :--- | :--- |
| [moleculeField](./moleculeField/README.md) | 分子空間を1つ作成します。 |