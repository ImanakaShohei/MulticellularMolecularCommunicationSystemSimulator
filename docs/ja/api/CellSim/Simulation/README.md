# Simulation クラス
シミュレーション全体を統括します。

```c++
class Simulation final;
```

## 静的メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [Current()](./Current.md) | 直近にアクセスしたSimulationインスタンスを取得します。 |

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [Simulation(SimulationOption, ::nlohmann::json)](./Simulation1.md) | インスタンスを作成します。 |
| Simulation(Simulation const&) | このコンストラクターは明示的に削除されています。 |

## デストラクター
| 形式 | 説明 |
| :--- | :--- |
| ~Simulation() | ヒープに確保した領域を解放します。 |

## 演算子
| 演算子名 | 説明 |
| :--- | :--- |
| operator=(Simulation const&) | この演算子は明示的に削除されています。 |

## メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [CellAlgorithmPtr()](./CellAlgorithmPtr.md) | 使用する最適化アルゴリズムインスタンスへのポインターを取得します。 |
| [CellListPtr()](./CellListPtr.md) | クラスタモデルで使用するCellListインスタンスへのポインターを取得します。 |
| [CellSimulationModelPtr()](./CellSimulationModelPtr.md) | 使用するシミュレーションモデルインスタンスへのポインターを取得します。 |
| [Cells()](./Cells.md) | Cellインスタンスが格納されたリストへの参照を取得します。 |
| [Current()](./Current.md) | 直近にアクセスしたSimulationインスタンスを取得します。 |
| [Molecules()](./Molecules.md) | MoleculeFieldインスタンスが格納されたリストへの参照を取得します。 |
| [Run()](./Run.md) | シミュレーションを実行します。 |
