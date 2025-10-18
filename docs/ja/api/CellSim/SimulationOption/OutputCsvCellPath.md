# SimulationOption::OutputCsvCellPath() 関数
細胞のcsvデータの出力ディレクトリのパスを取得します。

```c++
[[nodiscard]]
constexpr ::std::string const& OutputCsvCellPath() const noexcept;
```

## 戻り値
`::std::string const&`<br>
細胞のsvデータの出力ディレクトリのパス

## 解説

[コンストラクター](./SimulationOption1.md)で`outputPath`に相対パスを指定した場合、この関数は相対パスを返します。
絶対パスを指定した場合は、絶対パスを返します。