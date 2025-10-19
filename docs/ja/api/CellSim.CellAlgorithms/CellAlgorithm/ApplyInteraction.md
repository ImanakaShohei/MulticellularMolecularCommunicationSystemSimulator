# ApplyInteraction(const Simulation*, CellAlgorithmInteractionArgs) 関数
アルゴリズム側で完全な相互作用の計算を行う場合の処理を記述します。

```c++
virtual void ApplyInteraction(
    const Simulation* sender,
    CellAlgorithmInteractionArgs args
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `sender` | [`const Simulation*`](../../CellSim/Simulation/README.md) | この関数を呼び出したSimulationインスタンス |
| `args` | [`CellAlgorithmInteractionArgs`](../CellAlgorithmInteractionArgs/README.md) | 処理に必要な情報 |

## 解説
この関数は、デフォルトでは何も処理しません。