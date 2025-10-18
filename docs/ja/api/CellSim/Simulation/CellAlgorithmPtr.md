# Simulation::CellAlgorithmPtr() 関数
シミュレーションで使用する最適化アルゴリズムへのポインターを取得します。

```c++
[[nodiscard]]
constexpr const CellAlgorithms::CellAlgorithm* CellAlgorithmPtr() const noexcept;
```

## 戻り値
[`const CellAlgorithms::CellAlgorithm*`](../../CellSim.CellAlgorithms/CellAlgorithm/README.md)<br>
シミュレーションで使用する最適化アルゴリズムへのポインター

## 解説
使用するシミュレーションモデルの[UseCellAlgorithm()](../../CellSim.Model/CellSimulationModel/UseCellAlgorithm.md)が`false`の場合は`nullptr`が返されます。