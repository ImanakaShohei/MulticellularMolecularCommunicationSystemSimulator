# Version::Patch() 関数
CellSimのパッチバージョンを表します。

```c++
[[nodiscard]]
static constexpr int Patch() noexcept;
```

## 戻り値
`int`<br>
パッチバージョンを表す整数値

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