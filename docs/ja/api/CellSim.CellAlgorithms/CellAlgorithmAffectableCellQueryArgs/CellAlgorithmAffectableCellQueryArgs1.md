# CellAlgorithmAffectableCellQueryArgs::CellAlgorithmAffectableCellQueryArgs(const ::std::vector&lt;Cells::Cell&gt;\*, const ::std::vector&lt;Molecular::MoleculeField&gt;\*, const Cells::Cell\*) コンストラクター
メンバーの値を指定してインスタンスを作成します。

```c++
constexpr CellAlgorithmAffectableCellQueryArgs(
    const Cells::Cell* target,
    const ::std::vector<Cells::Cell>* cells,
    const ::std::vector<Molecular::MoleculeField>* fields
) noexcept;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `target` | [`const Cells::Cell*`](../../CellSim.Cells/Cell/README.md) | ターゲットの細胞インスタンス |
| `cells` | const ::std::vector&lt;[`Cells::Cell`](../../CellSim.Cells/Cell/README.md)&gt;* | 全ての細胞インスタンスが格納されたリスト |
| `fields` | const ::std::vector&lt;[`Molecular::MoleculeField`](../../CellSim.Molecular/MoleculeField/README.md)&gt;* | 全ての分子空間インスタンスが格納されたリスト |