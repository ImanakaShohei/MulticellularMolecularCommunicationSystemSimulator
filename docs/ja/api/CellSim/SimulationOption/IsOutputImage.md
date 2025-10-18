# SimulationOption::IsOutputImage() 関数
結果を画像出力するかどうかを示す値を取得します。

```c++
[[nodiscard]]
constexpr bool IsOutputImage() const noexcept;
```

## 戻り値
`bool`
結果を画像出力する場合は`true`、出力しない場合は`false`。