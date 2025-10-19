# CellAlgorithmStepArgs::CellAlgorithmStepArgs(const ::std::vector&lt;Cells::Cell&gt;\*, const ::std::vector&lt;Molecular::MoleculeField&gt;\*)コンストラクター
メンバーの値を指定してインスタンスを作成します。

```c++
constexpr CellAlgorithmStepArgs(
    const ::std::vector<Cells::Cell>* cells,
    const ::std::vector<Molecular::MoleculeField>* fields
) noexcept;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `cells` | const ::std::vector&lt;[`Cells::Cell`](../../CellSim.Cells/Cell/README.md)&gt;* | 全ての細胞インスタンスが格納されたリスト |
| `fields` | const ::std::vector&lt;[`Molecular::MoleculeField`](../../CellSim.Molecular/MoleculeField/README.md)&gt;* | 全ての分子空間インスタンスが格納されたリスト |