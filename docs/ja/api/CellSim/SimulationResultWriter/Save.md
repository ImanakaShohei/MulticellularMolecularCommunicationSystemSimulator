# SimulationResultWriter::Save() 関数
1ステップ分のデータを出力します。

```c++
void Save(
    Simulation const& simulation,
    uint64_t step
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `simulation` | [`Simulation const&`](../Simulation/README.md) | シミュレーションインスタンス |
| `step` | `uint64_t` | ステップ数 |

## 解説
オプションで指定したデータのみが出力されます。
出力データがない場合、この関数は何も出力しません。
また、出力ファイル名の形式は`{ステップ数}.extension`です。
ステップ数が[`Settings::Config::Simulation::TotalSteps()`](../../CellSim.Settings/Config/Simulation/TotalSteps.md)より桁が小さい場合、出力ファイル名は足りない分だけゼロ埋めされます。