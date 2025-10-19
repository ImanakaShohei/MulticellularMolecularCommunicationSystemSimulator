# simulation パラメータ
シミュレーション全体の設定を行います。

```json
"simulation": {
    "type": "object"
}
```

## 必須パラメータ
| 名前 | 説明 |
| :--- | :--- |
| [deltaTime](./deltaTime/README.md) | 1ステップで進む時間を指定します。 |
| [enable2dMode](./enable2dMode/README.md) | シミュレーションを2Dで行うか3D行うかを選択します。 |
| [fieldRadius](./fieldRadius/README.md) | シミュレーション空間の範囲を指定します。 |
| [imageSize](./imageSize/README.md) | 出力画像の1辺のピクセル数を指定します。 |
| [outputInterval](./outputInterval/README.md) | 何ステップ毎にデータを出力するかを指定します。 |
| [totalSteps](./totalSteps/README.md) | シミュレーションの総ステップ数を指定します。 |