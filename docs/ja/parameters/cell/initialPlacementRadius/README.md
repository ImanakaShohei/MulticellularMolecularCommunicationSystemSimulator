# initialPlacementRadius パラメーター
細胞の初期配置の範囲を指定します。

```json
"initialPlacementRadius": {
    "type": "number",
    "exclusiveMinimum": 0
}
```

## 型
`number`

## 値の範囲
`value > 0`

## 解説
細胞は原点を中心とした半径`value`の球または円の内部に初期配置されます。