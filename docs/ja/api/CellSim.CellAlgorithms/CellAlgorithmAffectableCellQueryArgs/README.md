# CellAlgorithmAffectableCellQueryArgs 構造体
[CellAlgorithm::GetAffectableCellInfos(const Simulation*, CellAlgorithmAffectableCellQueryArgs)](../CellAlgorithm/GetAffectableCellInfos.md)と[CellAlgorithm::IterateAffectableCellInfos(const Simulation*, CellAlgorithmAffectableCellQueryArgs)](../CellAlgorithm/IterateAffectableCellInfos.md)に渡す情報を格納します。

```c++
struct CellAlgorithmAffectableCellQueryArgs;
```

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [CellAlgorithmAffectableCellQueryArgs(const ::std::vector&lt;Cells::Cell&gt;\*, const ::std::vector&lt;Molecular::MoleculeField&gt;\*, const Cells::Cell\*)](./CellAlgorithmAffectableCellQueryArgs1.md) | メンバーの値を指定してインスタンスを作成します。 |

## メンバー
| 名前 | 説明 |
| :--- | :--- |
| [Cells](./Cells.md) | 全ての細胞インスタンスが格納されたリスト。 |
| [Fields](./Fields.md) | 全ての分子空間インスタンスが格納されたリスト。 |
| [Target](./Target.md) | ターゲットの細胞インスタンス。 |