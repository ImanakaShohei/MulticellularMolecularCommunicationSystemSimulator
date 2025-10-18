# Messages.IsInitialized() 関数
クラスが初期化されているかの状態を取得します。

```c++
[[nodiscard]]
static bool IsInitialized() noexcept;
```

## 戻り値
`bool`<br>
すでにクラスが初期化されている場合は`true`、初期化されていない場合は`false`

## 解説
[Initialize()](./Initialize.md)で初期化を行わない場合、[Get(::std::string const&)](./Get.md)でメッセージを取得することはできません。