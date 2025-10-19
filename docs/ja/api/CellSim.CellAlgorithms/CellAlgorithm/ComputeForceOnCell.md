# CellAlgorithm::ComputeForceOnCell(const Simulation*, CellAlgorithmForceComputationArgs) 関数
アルゴリズム側で相互作用の計算を行う場合の処理を記述します。

```c++
[[nodiscard]]
virtual Numerics::Vector3 ComputeForceOnCell(
    const Simulation* sender,
    CellAlgorithmForceComputationArgs args
) const;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `sender` | [`const Simulation*`](../../CellSim/Simulation/README.md) | この関数を呼び出したSimulationインスタンス |
| `args` | [`CellAlgorithmForceComputationArgs`](../CellAlgorithmForceComputationArgs/README.md) | 処理に必要な情報 |

## 戻り値
[`Numerics::Vector3`](../../CellSim.Numerics/Vector3/README.md)

## 解説
デフォルトではゼロベクトルが返されます。