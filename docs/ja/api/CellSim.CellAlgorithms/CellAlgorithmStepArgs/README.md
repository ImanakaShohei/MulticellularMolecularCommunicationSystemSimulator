# CellAlgorithmStepArgs 関数
[BeforeAdvanceStep(const Simulation*, CellAlgorithmStepArgs)](../CellAlgorithm/BeforeAdvanceStep.md)と[OnAdvanceStep(const Simulation*, CellAlgorithmStepArgs)](../CellAlgorithm/OnAdvanceStep.md)に渡す情報を格納します。

```c++
struct CellAlgorithmStepArgs;
```

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [CellAlgorithmStepArgs(const ::std::vector&lt;Cells::Cell&gt;\*, const ::std::vector&lt;Molecular::MoleculeField&gt;\*)](./CellAlgorithmStepArgs1.md) | メンバーの値を指定してインスタンスを作成します。 |

## メンバー
| 名前 | 説明 |
| :--- | :--- |
| [Cells](./Cells.md) | 全ての細胞インスタンスが格納されたリスト。 |
| [Fields](./Fields.md) | 全ての分子空間インスタンスが格納されたリスト。 |