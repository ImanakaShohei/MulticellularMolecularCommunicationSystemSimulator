# CellAlgorithmForceComputationArgs 構造体
[CellAlgorithm::ComputeForceOnCell(const Simulation*, CellAlgorithmForceComputationArgs)](../CellAlgorithm/ComputeForceOnCell.md)に渡す情報を格納します。

```c++
struct CellAlgorithmForceComputationArgs;
```

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [CellAlgorithmForceComputationArgs(const Cells::Cell\*, const ::std::vector&lt;Cells::Cell&gt;\*, const ::std::vector&lt;Molecular::MoleculeField&gt;\*, const Model::CellSimulationModel\*)](./CellAlgorithmForceComputationArgs1.md) | メンバーの値を指定してインスタンスを作成します。 |

## メンバー
| 名前 | 説明 |
| :--- | :--- |
| [Cells](./Cells.md) | 全ての細胞インスタンスが格納されたリスト。 |
| [Fields](./Fields.md) | 全ての分子空間インスタンスが格納されたリスト。 |
| [SimulationModel](./SimulationModel.md) | シミュレーションモデルのインスタンス。 |
| [Target](./Target.md) | ターゲットの細胞インスタンス。 |