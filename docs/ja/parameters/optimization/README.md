# optimization パラメーター
スレッド数やメモリ使用量などの設定を行います。

```json
"optimization": {
    "type": "object"
}
```

## 必須パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [maxDegreeOfParallelism](./maxDegreeOfParallelism/README.md) | 並列化処理のスレッド数を指定します。 |
| [peformance](./peformance/README.md) | 最適化設定。 |