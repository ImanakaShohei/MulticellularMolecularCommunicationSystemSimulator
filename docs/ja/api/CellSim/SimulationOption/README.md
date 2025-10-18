# SimulationOption クラス
シミュレーションで使用するオプションと出力ディレクトリを定義します。

```c++
class SimulationOption;
```

## 静的メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [BinName()](./BinName.md) | バイナリデータの出力ディレクトリの名前を取得します。 |
| [CellsName()](./CellsName.md) | 細胞データの出力ディレクトリの名前を取得します。 |
| [CsvName()](./CsvName.md) | csvデータの出力ディレクトリの名前を取得します。 |
| [ImagesName()](./ImagesName.md) | 画像データの出力ディレクトリの名前を取得します。 |
| [MoleculesName()](./MoleculesName.md) | 分子データの出力ディレクトリの名前を取得します。 |

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| [SimulationOption(bool, bool, bool, bool, bool, ::std::string)](./SimulationOption1.md) | オプションを指定してインスタンスを作成します。 |

## メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [InitializeDirectories()](./InitializeDirectories.md) | オプションに指定されたディレクトリを作成します。 |
| [IsOutputBinary()](./IsOutputBinary.md) | 結果をバイナリデータとして出力するかどうかを示す値を取得します。 |
| [IsOutputCsv()](./IsOutputCsv.md) | 結果をcsvデータとして出力するかどうかを示す値を取得します。 |
| [IsOutputImage()](./IsOutputImage.md) | 結果を画像出力するかどうかを示す値を取得します。 |
| [IsOutputVideo()](./IsOutputVideo.md) | 結果を動画出力するかどうかを示す値を取得します。 |