# clusterRotation パラメーター
ClusterRotationModelのパラメーターを指定します。

```json
"clusterRotation": {
    "type": "object"
}
```

## 必須パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [adhesionDistanceThreshold](./adhesionDistanceThreshold/README.md) | 細胞同士がこの値より近いと接着力が働きます。 |
| [adhesionForceFactor](./adhesionForceFactor/README.md) | 接着力にかける係数を指定します。 |
| [centralForceFactor](./centralForceFactor/README.md) | 全ての細胞に対して働く中心力の係数を指定します。 |
| [repulsionFactor](./repulsionFactor/README.md) | 近すぎる細胞同士にかかる反発力の係数を指定します。 |
| [repulsionMaxDistance](./repulsionMaxDistance/README.md) | 細胞同士の距離がこの値より近いと反発力が働きます。 |