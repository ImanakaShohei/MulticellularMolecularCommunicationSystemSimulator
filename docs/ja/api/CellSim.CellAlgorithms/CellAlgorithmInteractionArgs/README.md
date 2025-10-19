# CellAlgorithmInteractionArgs 構造体
[CellAlgorithm::ApplyInteraction(const Simulation*, CellAlgorithmInteractionArgs)](../CellAlgorithm/ApplyInteraction.md)に渡す情報を格納します。

```c++
struct CellAlgorithmInteractionArgs;
```

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [CellAlgorithmInteractionArgs(::std::vector&lt;Cells::Cell&gt;\*, :std::vector&lt;Molecular::MoleculeField&gt;\*, const Model::CellSimulationModel\*)](./CellAlgorithmInteractionArgs1.md) | メンバーの値を指定してインスタンスを作成します。 |

## メンバー
| 名前 | 説明 |
| :--- | :--- |
| [Cells](./Cells.md) | 全ての細胞インスタンスが格納されたリスト。 |
| [Fields](./Fields.md) | 全ての分子空間インスタンスが格納されたリスト。 |
| [SimulationModel](./SimulationModel.md) | シミュレーションモデルのインスタンス。 |