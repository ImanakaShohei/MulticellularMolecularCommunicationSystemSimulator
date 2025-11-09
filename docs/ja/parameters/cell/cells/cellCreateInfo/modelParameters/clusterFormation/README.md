# clusterFormation パラメーター
ClusterFormationModelのパラメーターを指定します。

```json
"clusterFormation": {
    "type": "object"
}
```

## 必須パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [adhesiveRepulsionFactor](./adhesiveRepulsionFactor/README.md) | 接着した細胞同士にかかる反発力の係数を指定します。 |
| [lambda](./lambda/README.md) | 細胞同士の距離に応じた引力の減衰度合いを指定します。 |
| [remoteForceFactor](./remoteForceFactor/README.md) | 離れた細胞同士にかかる引力の係数を指定します。 |