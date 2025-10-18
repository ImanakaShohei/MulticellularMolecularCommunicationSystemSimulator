# SimulationOption::OutputCsvPath() 関数
csvデータの出力ディレクトリのパスを取得します。

```c++
[[nodiscard]]
constexpr ::std::string const& OutputCsvPath() const noexcept;
```

## 戻り値
`::std::string const&`<br>
csvデータの出力ディレクトリのパス

## 解説

[コンストラクター](./SimulationOption1.md)で`outputPath`に相対パスを指定した場合、この関数は相対パスを返します。
絶対パスを指定した場合は、絶対パスを返します。