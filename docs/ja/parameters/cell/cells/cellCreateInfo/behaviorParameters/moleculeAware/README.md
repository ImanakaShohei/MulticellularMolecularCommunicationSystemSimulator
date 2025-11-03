# moleculeAware パラメーター
MoleculeAwareCellBehaviorのパラメーターを指定します。

```json
"moleculeAware": {
    "type": "object"
}
```

## 必須パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [cellDivisionRadius](../normal/cellDivisionRadius/README.md) | 細胞の半径がこの値を超えると分裂します。 |
| [degradationRate](./degradationRate/README.md) | 分子の分解係数を指定します。 |
| [growthRate](../normal/growthRate/README.md) | 細胞の成長速度を指定します。 |
| [synthesisRate](./synthesisRate/README.md) | 分子の生成係数を指定します。 |