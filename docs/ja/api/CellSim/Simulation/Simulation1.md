# Simulation::Simulation(SimulationOption, ::nlohmann::json) コンストラクター
オプションとjson設定からインスタンスを作成します。

```c++
Simulation(
    SimulationOption option,
    ::nlohmann::json config
);
```

## 引数
| 変数名 | 型 | 説明 |
| :--- | :--- | :--- |
| `option` | [`SimulationOption`](../SimulationOption/README.md) | 適用するオプション |
| `config` | `::nlohmann::json` | パラメータデータ |

## 解説
インスタンスは、必ず1つだけ作成するようにしてください。
2つ以上のインスタンスが同時に存在すると、パラメータデータが適切に設定されなくなります。
