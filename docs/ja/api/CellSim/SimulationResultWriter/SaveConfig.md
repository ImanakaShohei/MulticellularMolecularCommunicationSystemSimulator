# SimulationResultWriter::SaveConfig(::nlohmann::json const&) 関数
シミュレーションに使用した設定データをjsonファイルとして出力します。

```c++
void SaveConfig(
    ::nlohmann::json const& j
) const;
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `j` | `::nlohmann::json const&` | 出力するjsonデータ |

## 解説
オプションで指定した出力ディレクトリに`config.json`という名前で出力されます。