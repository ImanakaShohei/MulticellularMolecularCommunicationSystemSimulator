# CellAlgorithmInteractionArgs::CellAlgorithmInteractionArgs(::std::vector&lt;Cells::Cell&gt;\*, :std::vector&lt;Molecular::MoleculeField&gt;\*, const Model::CellSimulationModel\*) コンストラクター
メンバーの値を指定してインスタンスを作成します。

```c++
constexpr CellAlgorithmInteractionArgs(
    ::std::vector<Cells::Cell>* cells,
    ::std::vector<Molecular::MoleculeField>* fields,
    const Model::CellSimulationModel* simulationModel
) noexcept;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `cells` | ::std::vector&lt;[`Cells::Cell`](../../CellSim.Cells/Cell/README.md)&gt;* | 全ての細胞インスタンスが格納されたリスト |
| `fields` | ::std::vector&lt;[`Molecular::MoleculeField`](../../CellSim.Molecular/MoleculeField/README.md)&gt;* | 全ての分子空間インスタンスが格納されたリスト |
| `simulationModel` | [`const Model::CellSimulationModel*`](../../CellSim.Model/CellSimulationModel/README.md) | シミュレーションモデル |