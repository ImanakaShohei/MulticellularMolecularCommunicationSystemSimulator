# SimulationOption::IsOutputVideo() 関数
結果を動画出力するかどうかを示す値を取得します。

```c++
[[nodiscard]]
constexpr bool IsOutputVideo() const noexcept;
```

## 戻り値
`bool`
結果を動画出力する場合は`true`、出力しない場合は`false`。