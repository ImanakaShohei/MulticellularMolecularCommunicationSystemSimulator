# SimulationOption::OutputBinaryMoleculePath() 関数
分子空間のバイナリデータの出力ディレクトリのパスを取得します。

```c++
[[nodiscard]]
constexpr ::std::string const& OutputBinaryMoleculePath() const noexcept;
```

## 戻り値
`::std::string const&`<br>
分子空間のバイナリデータの出力ディレクトリのパス

## 解説
[コンストラクター](./SimulationOption1.md)で`outputPath`に相対パスを指定した場合、この関数は相対パスを返します。
絶対パスを指定した場合は、絶対パスを返します。