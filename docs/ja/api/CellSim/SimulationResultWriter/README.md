# SimulationResultWriter クラス
シミュレーション結果を出力する機能を提供します。

```c++
class SimulationResultWriter final;
```

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [SimulationResultWriter(SimulationOption)](./SimulationResultWriter1.md) | オプションを指定してインスタンスを作成します。 |
| SimulationResultWriter(SimulationResultWriter const&) | このコンストラクターは明示的に削除されています。 |

## デストラクター
| 形式 | 説明 |
| :--- | :--- |
| ~SimulationResultWriter() | 動画出力する場合に、動画データストリームを閉じます。 |

## 演算子
| 演算子名 | 説明 |
| :--- | :--- |
| operator=(SimulationResultWriter const&) | この演算子は明示的に削除されています。 |

## メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [Initialize()](./Initialize.md) | 内部データを初期化します。 |
| [InitializeMoleculeData(::std::vector&lt;Molecular::MoleculeField&gt; const&)](./InitializeMoleculeData.md) | 分子空間の出力データを初期化します。 |
| [Save(Simulation const&, uint64_t)](./Save.md) | 1ステップ分のデータを出力します。 |
| [SaveResult(uint64_t, size_t, int64_t, Model::CellSimulationType, CellAlgorithms::CellAlgorithmType)](./SaveResult.md) | 最終結果を出力します。 |
| [SaveConfig(::nlohmann::json const&)](./SaveConfig.md) | シミュレーションに使用した設定データをjsonファイルとして出力します。 |