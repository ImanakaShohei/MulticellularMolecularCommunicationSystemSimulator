# initialDistribution パラメーター
分子の初期配置の分布を指定します。

```json
"initialDistribution": {
    "type": "string",
    "enum": [
        "Centered",
        "Uniform"
    ]
}
```

## 型
`string`

## プロパティ
| 名前 | 説明 |
| :--- | :--- |
| `Centered` | 全ての分子が原点に配置されます。 |
| `Uniform` | 全ての分子が均一に配置されます。 |

## 解説
ユーザー定義のBehavior作成を作成するときは、このプロパティの指示通りに分子を配置する必要があります。
[`NormalMoleculeBehavior`](../../../../api/CellSim.Molecular/NormalMoleculeBehavior/README.md)では、`Centered`設定時に、`gridCount`が奇数の場合は原点が含まれるグリッドにすべての分子が配置され、`gridCount`が偶数の場合は、原点の周辺の8つ(3Dのとき)または4つ(2Dのとき)のグリッドに分子を均等に配置します。
また、`Uniform`を選択した場合は境界部分以外のグリッドに対して均等に分子が配置されます。