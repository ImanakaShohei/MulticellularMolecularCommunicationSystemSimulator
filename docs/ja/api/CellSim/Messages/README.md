# Messages クラス
実行時に画面に表示するメッセージを管理します。
メッセージは`./languages`にある言語ファイルから取得します。

```c++
class Messages final;
```

## 静的メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [Get(::std::string const&)](./Get.md) | メッセージを取得します。 |
| [Initialize()](./Initialize.md) | クラス全体の機能を初期化します。 |
| [IsInitialized()](./IsInitialized.md) | クラスが初期化されているかを取得します。 |