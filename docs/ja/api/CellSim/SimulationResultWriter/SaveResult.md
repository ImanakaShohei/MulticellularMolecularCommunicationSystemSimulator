# SimulationResultWriter::SaveResult(uint64_t, size_t, int64_t, Model::CellSimulationType, CellAlgorithms::CellAlgorithmType) 関数
最終結果を出力します。

```c++
void SaveResult(
    uint64_t totalStep,
    size_t initialCellCount,
    int64_t totalMilliSeconds,
    Model::CellSimulationType simulationType,
    CellAlgorithms::CellAlgorithmType algorithmType
) const;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `totalStep` | `uint64_t` | 総ステップ数 |
| `initialCellCount` | `size_t` | 初期状態での細胞の総数 |
| `totalMilliSeconds` | `int64_t` | 実行にかかった時間(ミリ秒) |
| `simulationType` | [`Model::CellSimulationType`](../../CellSim.Model/CellSimulationType/README.md) | シミュレーションモデルの種類 |
| `algorithmType` | [`CellAlgorithms::CellAlgorithmType`](../../CellSim.CellAlgorithms/CellAlgorithmType/README.md)  | 最適化アルゴリズムの種類 |

## 解説
オプションで指定した出力ディレクトリに`result.txt`という名前で出力されます。