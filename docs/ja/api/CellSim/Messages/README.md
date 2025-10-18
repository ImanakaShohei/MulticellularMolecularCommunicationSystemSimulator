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

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| Messages() | このコンストラクターは明示的に削除されています。 |
| Messages(Messages const&) | このコンストラクターは明示的に削除されています。 |
| Messages(Message&&) | このコンストラクターは明示的に削除されています。 |

## デストラクター
| 形式 | 説明 |
| :--- | :--- |
| ~Messages() | デストラクターは明示的に削除されています。 |

## 演算子
| 演算子名 | 説明 |
| :--- | :--- |
| operator=(Messages const&) | この演算子は明示的に削除されています。 |
| operator=(Messages&&) | この演算子は明示的に削除されています。 |