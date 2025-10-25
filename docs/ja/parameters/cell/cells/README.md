# cells パラメーター
配置する細胞の情報を格納します。

```json
"cells": {
    "type": "array",
    "items": {
        "$ref": "#/$defs/cellCreateInfo"
    },
    "minItems": 1,
    "uniqueItems": true
}
```

## 要素型
| 名前 | 説明 |
| :--- | :--- |
| [cellCreateInfo](./cellCreateInfo/README.md) | 配置する細胞の情報を設定します。 |