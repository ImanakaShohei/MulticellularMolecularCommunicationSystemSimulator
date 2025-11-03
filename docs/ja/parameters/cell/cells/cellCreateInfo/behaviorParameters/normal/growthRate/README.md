# growthRate パラメーター
細胞の成長速度を指定します。

```json
"growthRate": {
    "type": "number",
    "exclusiveMinimum": 0
}
```

## 型
`number`

## 値の範囲
`value > 0`

## 解説
1stepで、半径が`value`×[`deltaTime`](../../../../../../simulation/deltaTime/README.md)だけ増加します。