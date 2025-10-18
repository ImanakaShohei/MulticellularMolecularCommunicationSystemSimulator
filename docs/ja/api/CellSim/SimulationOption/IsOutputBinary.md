# SimulationOption::IsOutputBinary() 関数
結果をバイナリデータとして出力するかどうかを示す値を取得します。

```c++
[[nodiscard]]
constexpr bool IsOutputBinary() const noexcept;
```

## 戻り値
`bool`
結果をバイナリデータとして出力する場合は`true`、出力しない場合は`false`。