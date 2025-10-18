# Simulation::Current() 関数
直近にアクセスしたSimulationインスタンスを取得します。

```c++
[[nodiscard]]
static const Simulation* Current() noexcept;
```

## 戻り値
直近にアクセスしたSimulationインスタンスへのポインター

## 解説
まだSimulationインスタンスを作成していない場合、`nullptr`が返されます。