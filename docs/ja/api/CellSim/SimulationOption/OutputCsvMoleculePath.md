# SimulationOption::OutputCsvMoleculePath() 関数
分子空間のcsvデータの出力ディレクトリのパスを取得します。

```c++
[[nodiscard]]
constexpr ::std::string const& OutputCsvMoleculePath() const noexcept;
```

## 戻り値
`::std::string const&`<br>
分子空間のcsvデータの出力ディレクトリのパス

## 解説

[コンストラクター](./SimulationOption1.md)で`outputPath`に相対パスを指定した場合、この関数は相対パスを返します。
絶対パスを指定した場合は、絶対パスを返します。