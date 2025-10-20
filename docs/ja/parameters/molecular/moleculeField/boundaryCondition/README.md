# boundaryCondition パラメーター
境界条件を選択します。

```json
"boundaryCondition": {
    "type": "string",
    "enum": [
        "Absorbing",
        "Periodic",
        "Reflective"
    ]
}
```
## 型
`string`

## プロパティ
| 名前 | 説明 |
| :--- | :--- |
| `Absorbing` | Dirichlet条件：境界で吸収される。 |
| `Reflective` | Neumann条件：壁のように跳ね返る。 |
| `Periodic` | PBC条件：反対側に回り込む。 |
