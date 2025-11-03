# cellDivisionRadius パラメーター
細胞の半径がこの値を超えると分裂します。

```json
"cellDivisionRadius": {
    "type": "number",
    "exclusiveMinimum": 0
}
```

## 型
`number`

## 値の範囲
`value > 0`

## 解説
クラスタモデルを併用する場合は、クラスターの半径がこの値を超えないように指定してください。