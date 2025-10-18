# Version::Minor() 関数
CellSimのマイナーバージョンを表します。

```c++
[[nodiscard]]
static constexpr int Minor() noexcept;
```

## 戻り値
`int`<br>
マイナーバージョンを表す整数値

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