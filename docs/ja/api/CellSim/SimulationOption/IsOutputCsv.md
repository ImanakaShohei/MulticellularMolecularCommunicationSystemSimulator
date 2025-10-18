# SimulationOption::IsOutputCsv() 関数
結果をcsvデータとして出力するかどうかを示す値を取得します。

```c++
[[nodiscard]]
constexpr bool IsOutputCsv() const noexcept;
```

## 戻り値
`bool`
結果をcsvデータとして出力する場合は`true`、出力しない場合は`false`。