# Messages::Get(::std::string const&) 関数
メッセージを取得します。

```c++
[[nodiscard]]
static ::std::string const& Get(
    ::std::string const& name
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| name | ::std::string const& | メッセージに関連付けられた名前 |

## 戻り値
`::std::string const&`<br>
メッセージ本文

## 解説
存在しない名前を指定すると空文字列が返されます。

## 例
```c++
::puts(Messages::Get("Simulation.Run.Running").c_str());
```
