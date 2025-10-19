# maxDegreeOfParallelism パラメーター
並列化処理のスレッド数を指定します。

```json
"maxDegreeOfParallelism": {
    "type": "integer"
}
```

## 型
`integer`

## 解説
値をゼロ以下にした場合、CellSimはCPUの論理プロセッサ数で並列処理を行います。
CPUの論理プロセッサ数が512以下の場合、並列処理可能な最大スレッド数は512です。
512より大きい場合は、そのCPUの論理プロセッサ数が並列処理可能な最大スレッド数になります。