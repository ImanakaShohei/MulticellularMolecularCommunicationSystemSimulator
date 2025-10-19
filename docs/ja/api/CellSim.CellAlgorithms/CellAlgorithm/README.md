# CellAlgorithm クラス
高速化アルゴリズムの基底クラスです。
このクラスの仮想関数をオーバーライドすることで、独自の最適化アルゴリズムを作成できます。

```c++
class CellAlgorithm;
```

## 静的メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [FromType(CellAlgorithmType)](./FromType.md) | CellAlgorithmTypeからインスタンスを作成します。 |

## デストラクター
| 形式 | 説明 |
| :--- | :--- |
| [~CellAlgorithm()](./~CellAlgorithm.md) | `virtual`指定されたデフォルトデストラクタです。 |

## メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [ApplyInteraction(const Simulation*, CellAlgorithmInteractionArgs)](./ApplyInteraction.md) | アルゴリズム側で完全な相互作用の計算を行う場合の処理を記述します。 |
| [CellListPtr()](./CellListPtr.md) | クラスタモデルで使用するCellListインスタンスへのポインターを取得します。 |
| [CellSimulationModelPtr()](./CellSimulationModelPtr.md) | 使用するシミュレーションモデルインスタンスへのポインターを取得します。 |
| [Cells()](./Cells.md) | Cellインスタンスが格納されたリストへの参照を取得します。 |
| [Current()](./Current.md) | 直近にアクセスしたSimulationインスタンスを取得します。 |
| [Molecules()](./Molecules.md) | MoleculeFieldインスタンスが格納されたリストへの参照を取得します。 |
| [Run()](./Run.md) | シミュレーションを実行します。 |
