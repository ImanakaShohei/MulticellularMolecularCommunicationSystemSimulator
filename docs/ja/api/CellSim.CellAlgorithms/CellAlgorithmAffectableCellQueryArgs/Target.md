# CellAlgorithmAffectableCellQueryArgs::Target
ターゲットの細胞インスタンスへのポインターです。

```c++
const Cells::Cell* Target;
```

## 型
[`const Cells::Cell*`](../../CellSim.Cells/Cell/README.md)

## 解説
[CellAlgorithm::GetAffectableCellInfos(const Simulation*, CellAlgorithmAffectableCellQueryArgs)](../CellAlgorithm/GetAffectableCellInfos.md)と[CellAlgorithm::IterateAffectableCellInfos(const Simulation*, CellAlgorithmAffectableCellQueryArgs)](../CellAlgorithm/IterateAffectableCellInfos.md)では、このインスタンスに力を加える細胞を選出します。