# Version クラス
CellSimのバージョン情報を提供します

```c++
class Version final;
```

## 静的メンバー関数
| 関数名 | 説明 |
| :--- | :--- |
| [Extension()](./Extension.md) | 追加で表示する文字列を表します。 |
| [Major()](./Major.md) | CellSimのメジャーバージョンを表します。 |
| [Minor()](./Minor.md) | CellSimのマイナーバージョンを表します。 |
| [Patch()](./Patch.md) | CellSimのパッチバージョンを表します。 |

## コンストラクター
| 形式 | 説明 |
| :--- | :--- |
| Version() | このコンストラクターは明示的に削除されています。 |
| Version(Version const&) | このコンストラクターは明示的に削除されています。 |
| Version(Version&&) | このコンストラクターは明示的に削除されています。 |

## デストラクター
| 形式 | 説明 |
| :--- | :--- |
| ~Version() | デストラクターは明示的に削除されています。 |

## 演算子
| 演算子名 | 説明 |
| :--- | :--- |
| operator=(Version const&) | この演算子は明示的に削除されています。 |
| operator=(Version&&) | この演算子は明示的に削除されています。 |