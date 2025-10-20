# colorIntensityThreshold パラメーター
画像・動画出力時の色分けする分子数の範囲を指定します。

```json
"colorIntensityThreshold": {
    "type": "number",
    "exclusiveMinimum": 0
}
```

## 型
`number`

## 値の範囲
`value > 0`

## 解説
色は分子数が多くなるにつれて、黒→青→緑→赤→白の順に変化していきます。
このパラメーターは「白」になる分子数を指定します。