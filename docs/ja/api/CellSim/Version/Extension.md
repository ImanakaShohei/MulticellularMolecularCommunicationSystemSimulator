# Version::Extension() 関数
追加で表示する文字列を表します。

```c++
[[nodiscard]]
static constexpr const char* Extension() noexcept;
```

## 戻り値
`const char*`<br>
C文字列

## 例
```c++
::printf(
    "%d.%d.%d %s\n",
    Version::Major(),
    Version::Minor(),
    Version::Patch(),
    Version::Extension()
);
```