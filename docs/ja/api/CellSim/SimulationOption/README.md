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
| [MoleculesName()](./MoleculesName.md) | 分子空間データの出力ディレクトリの名前を取得します。 |

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
| [OutputBinaryPath()](./OutputBinaryPath.md) | バイナリデータの出力ディレクトリのパスを取得します。 |
| [OutputBinaryCellPath()](./OutputBinaryCellPath.md) | 細胞のバイナリデータの出力ディレクトリのパスを取得します。 |
| [OutputBinaryMoleculePath()](./OutputBinaryMoleculePath.md) | 分子空間のバイナリデータの出力ディレクトリのパスを取得します。 |
| [OutputCsvCellPath()](./OutputCsvCellPath.md) | 細胞のcsvデータの出力ディレクトリのパスを取得します。 |
| [OutputCsvMoleculePath()](./OutputCsvMoleculePath.md) | 分子空間のcsvデータの出力ディレクトリのパスを取得します。 |
| [OutputCsvPath()](./OutputCsvPath.md) | csvデータの出力ディレクトリのパスを取得します。 |
| [OutputImageMoleculePath()](./OutputImageMoleculePath.md) | 分子空間の画像出力ディレクトリのパスを取得します。 |
| [OutputImagePath()](./OutputImagePath.md) | 画像出力ディレクトリのパスを取得します。 |
| [OutputPath()](./OutputPath.md) | 出力ディレクトリのパスを取得します。 |