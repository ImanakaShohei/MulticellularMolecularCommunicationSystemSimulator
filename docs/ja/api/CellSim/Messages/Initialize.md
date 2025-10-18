# Messages::Initialize() 関数
メッセージを言語ファイルから取得し、クラス全体の機能を初期化します。

```c++
static bool Initialize();
```

## 戻り値
初期化に成功したかどうか

## 解説
初期化を行わない場合、[Get(::std::string const&)](./Get.md)でメッセージを取得することはできません。
また、既に初期化が完了している場合は`false`が返されます。