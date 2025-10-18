# Simulation::CellAlgorithmPtr() 関数
シミュレーションで使用する最適化アルゴリズムへのポインターを取得します。

```c++
[[nodiscard]]
constexpr const Model::CellSimulationModel* CellSimulationModelPtr() const noexcept;
```

## 戻り値
[`const Model::CellSimulationModel*`](../../CellSim.Model/CellSimulationModel/README.md)<br>
シミュレーションで使用する最適化アルゴリズムへのポインター