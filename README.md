# Multicellular Molecular Communication System Simulator
![gif](https://github.com/saikiRA1011/CellNetworkShapeSimulation/blob/main/readme_img/sim.gif)

# Overview
分子通信シミュレーションのための汎用シミュレータであり、ユーザがシミュレーションのパラメータや力学作用を定義することでさまざまなモデルに対応したシミュレーションを実行することができます。

tutorial  
jp -> https://github.com/saikiRA1011/CellNetworkShapeSimulation/blob/main/tutorial/out/tutorial.pdf

# 動作要件
- C++20をサポートするコンパイラ
- Python3系(必要ライブラリはrequirements.txtから取得可能)
- pip
- CMake (version 3.11以降)
- Windows or mac OS or Linux

Pythonの必要ライブラリは以下のコマンドで一括インストールできます。  
`pip install -r requirements.txt`

# 使い方
### Step 1
シミュレータを`build`する。  
  
`Windows`の場合
```sh
.\Build-Windows.bat
```
`macOS`の場合
```sh
$ chmod +x Build-macOS.sh
$ ./Build-macOS.sh
```
`Linux`の場合
```sh
$ chmod +x Build-Linux.sh
$ ./Build-Linux.sh
```

### Step 2
シミュレータを実行する。  
buildしたシミュレータはMSVCの場合は`./build/Release/`に、それ以外の場合は`./build/`にあります。  
```sh
./SimMain run
```

### Step 3
実行結果を動画に変換する。  
```sh
./SimMain convert
```

### Step 4
変換した動画を確認する。  
```sh
./SimMain open
```
  
  
ただし、Step 2 ~ Step 4は`./SimMain all`でまとめて実行することもできます。
また、各種コマンドは`./SimMain help`から確認することができます。

# シミュレーションモデルの作成方法
`src/UserSimulationModel.cpp(.hpp)`と`src/UserCellAlgorithm.cpp(.hpp)`と`src/UserCell.cpp(.hpp)`にモデルを記述します。  <!-- 現在作成可能なモデルは細胞間に働く力学モデル(calcCellCellForce)のみです。   -->
シミュレーションのパラメータは`SimMain`と同じフォルダにある`config.yaml`に記述します。ユーザが記述するプログラムはこの4つです。  

## 最適化アルゴリズム
シミュレーション時間を短縮する最適化アルゴリズムを独自に作成できます。
基底クラス`CellAlgorithm`にある4つの仮想関数をオーバーライドしてください。
```c++
virtual void beforeNextStep(const ::std::vector<Cell*>&, const ::std::vector<UserMoleculeSpace*>&);
virtual void onNextStep(const ::std::vector<Cell*>&, const ::std::vector<UserMoleculeSpace*>&);
virtual Generator<CellInfo> iterateAffectableCellInfos(Cell& c, const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
virtual ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
```
### beforeNextStep()
細胞に力を加える前にする処理を記述します。
この関数の実装は任意です。

### onNextStep()
細胞の位置更新後にする処理を記述します。
この関数の実装も任意です。

### iterateAffectableCellInfos()
ターゲットに力を加えることができる細胞の情報をコルーチン`co_yield`で1つ1つ返します。
この関数は設定で`optimization: performance`が`LOW-MEMORY`に設定されている時に各シミュレーションモデルで細胞に力を加える時に呼ばれます。
複数スレッドから呼ばれるのでデータ競合が起こらないように設計してください。

### getAffectableCellInfos()
ターゲットに力を加えることができる細胞の情報をリストにして返します。
この関数は設定で`optimization: performance`が`FAST`に設定されている時に呼ばれます。
この関数がよばれるタイミングは`iterateAffectableCellInfos()`と同様です。

### 定義済みアルゴリズム
このシミュレータには3つの定義済みアルゴリズムがあります。
独自アルゴリズムを設計する際に参考にしてください。
  * ナイーブなアルゴリズム(`src/core/NaiveAlgorithm.cpp(.hpp)`)
  * Barnes-Hutアルゴリズム(`src/core/BarnesHut.cpp(.hpp)`)  
  * CellList(`src/core/CellList.cpp(.hpp)`)

## シミュレーションモデル
`UserSimulationModel`の基底クラスである`CellSimulationModel`には４つの仮想関数があります。これらをオーバーライドすることで独自のモデルを作成できます。
```c++
virtual void initCells(::std::vector<Cell*>& cells);
virtual Vec3 calcCellForce(Cell& c, const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
virtual void beforeNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
virtual void onNextStep(::std::vector<Cell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces);
```

### initCells()
ここでは各細胞の初期配置を決めます。デフォルトでは円の内部に細胞を敷き詰めるようになっています。

### calcCellForce()
ここでは、ターゲットの細胞にどのような力を加えるかを記述します。
基底クラス`CellSimulationModel`に最適化アルゴリズムのインスタンスへの参照`m_cellAlgorithm`があるので、
それを使うことでシミュレーションの高速化ができます。
この関数は複数スレッドから呼ばれるため、データの競合が起こらないように設計してください。
また、最適化アルゴリズムを使用する際は、設定の`optimization: performance`と連動するように設計すると良いです。
この値が、`LOW-MEMORY`の時には`iterateAffectableCellInfos()`を、`FAST`の時は`getAffectableCellInfos()`を呼ぶようにすると他の定義済みモデルとの動作の整合性が取れます。

### beforeNextStep()
細胞に力を加える前にする処理を記述します。
この関数の実装は任意です。

### onNextStep()
細胞の位置更新後にする処理を記述します。
この関数の実装も任意です。

### 定義済みモデル
このシミュレータには5つの定義済みモデルがあります。
独自モデルを設計する際に参考にしてください。
  * クラスタ形成モデル(`src/core/ClusterFormationModel.cpp(.hpp)`)  
  * 細胞塊成長モデル(`src/core/MassGrowthModel.cpp(.hpp)`)  
  * 細胞塊回転モデル(`src/core/MassRotationModel.cpp(.hpp)`)  
  * ネットワーク形成モデル(`src/core/NetworkFormationModel.cpp(.hpp)`)  
  * 信号分子拡散モデル(`src/core/SignalMoleculeDiffusionModel.cpp(.hpp)`)

# 特長
- CellListなどのアルゴリズムを利用することによりシミュレーションを高速に実行することが可能となっています。  
- シミュレーションの結果をテキスト(`./result/*`)に出力しているため、ユーザが独自にビジュアライザを作成し、再利用することもできます。

# Tips
ドキュメントの生成にDoxygenを利用しているので、Doxygenの環境を用意することで各クラスやメソッドの説明を簡単に見ることができます。

# References
- S. Imanaka and T. Nakano, ``Algorithm Design for Multicellular Molecular Communication Simulations,'' 7th International Conference on Knowledge Innovation and Invention 2024 (ICKII 2024), Aichi, Aug. 2024.
- S. Imanaka, T. Saiki and T. Nakano, ``Accelerating Multicellular Molecular Communication Simulations Using the Barnes-Hut Algorithm,'' 2024 IEEE 4th International Conference on Electronic Communications,Internet of Things and Big Data (ICIEB 2024),  Taiwan, April 2024.
- T. Saiki and T. Nakano, ``A Simulation Platform for Dynamic Multicellular Molecular Communication Systems ,'' 2024 IEEE 4th International Conference on Electronic Communications,Internet of Things and Big Data (ICIEB 2024),  Taiwan, April 2024.
- S. Takanori and T. Nakano, ``Design and Implementation of a General-purpose Multicellular Molecular Communication Simulator,'' 14th EAI International Conference on Bio-inspired Information and Communications Technologies (BICT 2023), Okinawa, April 2023.
- T. Saiki and T. Nakano, ``Design and Implementation of a Multicellular Molecular Communication Simulator," full paper, in Proc. 2022 Joint 12th International Conference on Soft Computing and Intelligent Systems and 23rd International Symposium on Advanced Intelligent Systems (SCIS&ISIS 2022), Mie, Nov.--Dec. 2022.

# Author
所属 : https://sites.google.com/c.info.eng.osaka-cu.ac.jp/ect/%E3%83%9B%E3%83%BC%E3%83%A0
