# imageSize プロパティ
出力画像の1辺のピクセル数を指定します。

```json
"imageSize": {
    "type": "integer",
    "exclusiveMinimum": 0
}
```

## 型
`integer`

## 値の範囲
`value > 0`

## 解説
コマンドラインオプションで、`-i` `--image` `-v` `--video`のいずれかが指定されている場合、出力画像または出力動画のピクセル数は`value`×`value`になります。