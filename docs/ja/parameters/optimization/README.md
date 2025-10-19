# optimization パラメータ
スレッド数やメモリ使用量などの設定を行います。

```json
"optimization": {
    "type": "object"
}
```

## 必須パラメータ
| 名前 | 説明 |
| :--- | :--- |
| [maxDegreeOfParallelism](./maxDegreeOfParallelism/README.md) | 並列化処理のスレッド数を指定します。 |
| [peformance](./peformance/README.md) | 最適化設定。 |