# 更新履歴

## [2.0.0 Beta 9] 2025-08-13
### 新機能
- 分子データを.bin, .csv, .pngで出力する機能を追加
### 変更点
- 分子データが存在しない場合はmoleculeフォルダを生成しないように更新
### 不具合修正
- 2次元シミュレーション時にNormalMoleculeBehaviorが2次元ではなく、3次元の拡散方程式を計算してしまう問題を修正
- 分子が拡散しない問題を修正

## [2.0.0 Beta 8] 2025-08-10
### 新機能
- Colorを追加
- CellCreateInfoを追加
- CellTypeにAddName()、Color, Id、Nameを追加<!--C++-->
- MoleculeKindにAddName()、Id、Nameを追加<!--C++-->
- config.jsonで複数種類のCellを指定できるように更新<!--C++-->
- 画像・動画出力時のCellの色を指定できるように更新<!--C++-->
- <!--C++版で-->ターゲット環境がARMかx86かを判定するマクロを追加
- MoleculeFieldを動画出力する機能を追加<!--C++-->
### 変更点
- Cellの等値判定を「Idの一致」から「アドレスの一致」に変更
### 破壊的変更
- CellTypeをenumからclassに変更<!--C++-->
- MoleculeKindをenumからclassに変更<!--C++-->
### 不具合修正
- .csvと.binにCellのIsAliveプロパティが出力されない問題を修正


## [2.0.0 Beta 7] 2025-07-23
### 新機能
- ダミーCellを作成するCell.CreateDummy()を追加
- Cellにthisがダミーであるかを判定するプロパティIsDummyを追加
- WavePropagationCellBehaviorを追加
### 変更点
- CellSimulationModel.ComputeForceOnCell(sender, args)のargs.CellAlgorithmがnullの時、ナイーブなアルゴリズムとして実行するように変更
- ナイーブなアルゴリズム使用時にパフォーマンスが向上
### 破壊的変更
- CellBehaviorのComputeMetabolicChange(), ComputeMoleculeEmitAmount()を削除し、代わりにComputeMolecularProcess()を追加
- <!--C++版の-->CellBehaviorのHasState()を削除し、代わりにIsReusable()を追加
- CellのAppendMoleculeUnsafe()を削除
- CellのEmitMolecule(), Metabolize()を削除し、代わりにProcessMolecules()を追加
### 不具合修正
- UserSettingsが読み込まれない問題を修正
- CellAlgorithmをCellList以外にした状態でクラスタモデルを有効にするとアプリケーションがクラッシュする問題を修正
- CellAlgorithmをCellList以外にした状態でネットワーク形成モデルを動かそうとするとアプリケーションがクラッシュする問題を修正
<!--- C#版でCellのTypeが正しく設定されない問題を修正-->

## [2.0.0 Beta 6] 2025-07-09
### 新機能
- 出力画像・動画の縦横の長さを変更する設定を追加
- 並列処理を行うスレッド数の設定を追加
### 不具合修正
- `-p --param`で浮動小数点数を指定するとエラーが発生する問題を修正
- <!--C++版の-->CellSim.Cli.RepeatedValueOption.Values()が基底クラスの仮想関数Values()をオーバーライドしない問題を修正
<!-- - C#版を日本語環境で使った時に英語表記になってしまう問題を修正
- C#版で`-p --param`がうまく動作しない問題を修正
- C#版で`--param-sweep`がうまく動作しない問題を修正
- C#版でOpenCVのログが表示される問題を修正
-->

<!--
## [2.0.0 Beta 5] 2025-07-01
### 新機能
- パラメータオプション`-p --param`を追加
### 不具合修正
- クラスタ形成モデルの計算式の間違いを修正

-->