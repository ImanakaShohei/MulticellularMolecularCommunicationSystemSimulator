# simulationModel パラメーター
シミュレーションモデルの設定。

```json
"simulationModel": {
    "type": "object"
}
```

## 必須パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [simulationType](./simulationType/README.md) | シミュレーションモデルの種類を指定します。 |

## 任意パラメーター
| 名前 | 説明 |
| :--- | :--- |
| [clusterSprouting](./clusterSprouting/README.md) | クラスタスプラウトモデルのパラメーターのうち、細胞の種類に依存しないパラメータを指定します。 |
| [networkFormation](./networkFormation/README.md) | ネットワーク形成モデルのパラメーターのうち、細胞の種類に依存しないパラメータを指定します。 |