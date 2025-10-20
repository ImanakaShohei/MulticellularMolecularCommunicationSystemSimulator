# gridCount パラメーター
シミュレーション空間の1辺あたりのグリッド数を指定します。

```json
"gridCount": {
    "type": "integer",
    "exclusiveMinimum": 0
}
```

## 型
`integer`

## 値の範囲
`value > 0`

## 解説
シミュレーション空間に作成される総グリッド数は、3Dの場合は`value`×`value`×`value`、2Dの場合は`value`×`value`になります。