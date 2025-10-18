# Simulation::CellAlgorithmPtr() 関数
クラスタモデルで使用するCellListインスタンスへのポインターを取得します。

```c++
[[nodiscard]]
constexpr const CellAlgorithms::CellList* CellListPtr() const noexcept;
```

## 戻り値
[const CellAlgorithms::CellList*](../../CellSim.CellAlgorithms/CellList/README.md)<br>
クラスタモデルで使用するCellListインスタンスへのポインター

## 解説
クラスタモデルを使用しない場合は`nullptr`が返されます。