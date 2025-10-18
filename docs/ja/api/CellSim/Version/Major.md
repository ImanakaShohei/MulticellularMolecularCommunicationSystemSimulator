# Version::Major() 関数
CellSimのメジャーバージョンを表します。

```c++
[[nodiscard]]
static constexpr int Major() noexcept;
```

## 戻り値
`int`<br>
メジャーバージョンを表す整数値

## 例
```c++
::printf(
    "CellSim %d.%d.%d %s\n",
    Version::Major(),
    Version::Minor(),
    Version::Patch(),
    Version::Extension()
);
```