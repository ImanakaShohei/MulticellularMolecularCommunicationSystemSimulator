# SimulationResultWriter::InitializeMoleculeData() 関数
分子空間の出力データを初期化します。

```c++
void InitializeMoleculeData(
    ::std::vector<Molecular::MoleculeField> const& fields
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `fields` | ::std::vector<[`Molecular::MoleculeField`](../../CellSim.Molecular/MoleculeField/README.md)> const& | 分子空間リスト |

## 解説
この関数を呼ばない場合、[`Save(Simulation const&, uint64_t)`](./Save.md)分子空間データを出力しようとするとエラーが発生します。