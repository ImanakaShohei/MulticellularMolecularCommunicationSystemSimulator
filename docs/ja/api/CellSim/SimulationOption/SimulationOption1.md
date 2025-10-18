## SimulationOption::SimulationOption(bool, bool, bool, bool, bool, ::std::string) コンストラクター
オプションを指定してインスタンスを作成します。

```c++
SimulationOption(
    bool isOutputBinary,
    bool isOutputCsv,
    bool isOutputImage,
    bool isOutputVideo,
    bool cleanOutput,
    ::std::string outputPath
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `isOutputBinary` | `bool` | 結果をバイナリデータとして出力するかどうか |
| `isOutputCsv` | `bool` | 結果をcsvデータとして出力するかどうか |
| `isOutputImage` | `bool` | 結果を画像出力するかどうか |
| `isOutputVideo` | `bool` | 結果を動画出力するかどうか |
| `cleanOutput` | `bool` | 出力先のディレクトリが既に存在する場合に、ディレクトリを空にするかどうか |
| `outputPath` | `::std::string` | 出力ディレクトリのパス |

## 解説
`outputPath`にカレントディレクトリを指定しないでください。
CellSim本体を削除しようとしてエラーが発生する可能性があります。
