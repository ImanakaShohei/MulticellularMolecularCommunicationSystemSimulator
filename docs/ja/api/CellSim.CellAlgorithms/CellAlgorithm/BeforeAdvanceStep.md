# CellAlgorithm::BeforeAdvanceStep(const Simulation*, CellAlgorithmStepArgs) 関数
各ステップの前処理を記述します。

```c++
virtual void BeforeAdvanceStep(
    const Simulation* sender,
    CellAlgorithmStepArgs args
) = 0;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `sender` | [`const Simulation*`](../../CellSim/Simulation/README.md) | この関数を呼び出したSimulationインスタンス |
| `args` | [`CellAlgorithmStepArgs`](../CellAlgorithmStepArgs/README.md) | 処理に必要な情報 |

## 解説
この関数は派生クラスで必ずオーバーライドする必要があります。