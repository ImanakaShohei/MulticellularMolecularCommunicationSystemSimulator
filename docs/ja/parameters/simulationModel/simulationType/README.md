# simulationType パラメーター
シミュレーションモデルの種類を指定します。

```json
"simulationType": {
    "type": "string",
    "enum": [
        "CellGrowth",
        "ClusterFormation",
        "ClusterRotation",
        "ClusterSprouting",
        "NetworkFormation",
        "Null",
        "User"
    ]
}
```

## 型
`string`

## プロパティ
| 名前 | 説明 |
| :--- | :--- |
| `CellGrowth` | 細胞成長モデル。 |
| `ClusterFormation"` | クラスタ形成モデル。 |
| `ClusterRotation` | クラスタ回転モデル。 |
| `ClusterSprouting` | クラスタスプラウトモデル。 |
| `NetworkFormation` | ネットワーク形成モデル。 |
| `Null` | 何もしないモデル。 |
| `User` | ユーザー定義モデル。 |