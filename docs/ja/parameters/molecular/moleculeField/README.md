# moleculeField パラメーター
分子空間を1つ作成します。

```json
"moleculeField": {
    "type": "object"
}
```

## 必須パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [behaviorParameters](./behaviorParameters/README.md) | 各ふるまいのパラメーターを設定します。 |
| [behaviorType](./behaviorType/README.md) | 分子空間のふるまいの種類を選択します。 |
| [boundaryCondition](./boundaryCondition/README.md) | 境界条件を選択します。 |
| [colorIntensityThreshold](./colorIntensityThreshold/README.md) | 画像・動画出力時の色分けする分子数の範囲を指定します。 |
| [gridCount](./gridCount/README.md) | シミュレーション空間の1辺あたりのグリッド数を指定します。 |
| [initialDistribution](./initialDistribution/README.md) | 分子の初期配置の分布を指定します。 |
| [moleculeAmount](./moleculeAmount/README.md) | 初期配置する分子の量を指定します。 |
| [moleculeKind](./moleculeKind/README.md) | 分子空間の名前を指定します。 |