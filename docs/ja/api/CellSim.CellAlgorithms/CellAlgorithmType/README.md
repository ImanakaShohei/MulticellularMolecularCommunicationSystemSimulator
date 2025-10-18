# CellAlgorithmType 列挙型
高速化アルゴリズムの種類を表します。

```c++
enum class CellAlgorithmType;
```

## メンバー
| 名前 | 値 | 説明 |
| :--- | :--- | :--- |
| `BarnesHut` | `0` | Barnes-Hutアルゴリズム。 |
| `CellList` | `1` | CellList。 |
| `Naive` | `2` | ナイーブなアルゴリズム。 |
| `Null` | `3` | 何もしないアルゴリズム。 |
| `ParticleMesh` | `4` | Particle-Mesh。 |
| `User` | `5` | ユーザー定義のアルゴリズム。 |

## 解説
`ParticleMesh`は、このバージョンでは無効です。