# clusterSprouting パラメータ
クラスタスプラウトモデルのパラメータのうち、細胞の種類に依存しないパラメータを指定します。

```json
"clusterSprouting": {
    "type": "object"
}
```

## 必須パラメータ
| 名前 | 説明 |
| :--- | :--- |
| [contactDistance](./contactDistance/README.md) | 細胞同士の距離がこの値より小さいと反発力が発生します。 |