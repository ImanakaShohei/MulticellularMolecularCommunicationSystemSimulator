# CellAlgorithmAffectableCellQueryArgs::Target メンバー
ターゲットの細胞インスタンスへのポインターです。

```c++
const Cells::Cell* Target;
```

## 型
[`const Cells::Cell*`](../../CellSim.Cells/Cell/README.md)

## 解説
[CellAlgorithm::ComputeForceOnCell(const Simulation*, CellAlgorithmForceComputationArgs)](../CellAlgorithm/ComputeForceOnCell.md)では、このインスタンスに加える力を計算します。