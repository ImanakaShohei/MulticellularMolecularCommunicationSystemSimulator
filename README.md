# 準備中...
このページはまだ完成していません。  

# Overview
分子通信シミュレーションのための汎用シミュレータであり、ユーザがシミュレーションのパラメータや力学作用を定義することでさまざまなモデルに対応したシミュレーションを実行することができます。

# ビルド・動作要件
## C++の場合
- C++20をサポートするコンパイラ
- CMake (version 3.11~3.31)
- Windows or macOS or Linux

## C#の場合
- .NET 8 SDK

# ビルド方法
## C++の場合
`Windows`の場合
```sh
cd build-scripts
.\build-windows.bat
```

`macOS`の場合
```sh
$ cd build-scripts
$ chmod +x build-macos.sh
$ ./build-macos.sh
```

`Linux`の場合
```sh
$ cd build-scripts
$ chmod +x build-linux.sh
$ ./build-linux.sh
```

## C#の場合
`Windows(x64)`の場合
```sh
cd src/cs/CellSim
dotnet publish CellSim.csproj -p:PublishProfile=Properties\\PublishProfiles\\win-x64.pubxml
```

`Windows(arm64)`の場合
```sh
cd src/cs/CellSim
dotnet publish CellSim.csproj -p:PublishProfile=Properties\\PublishProfiles\\win-arm64.pubxml
```

`macOS(Apple Silicon Mac)`の場合
```sh
$ cd src/cs/CellSim
$ dotnet publish cellsim-macos.csproj -p:PublishProfile=Properties/PublishProfiles/osx-arm64.pubxml
```

`macOS(Intel Mac)`の場合
```sh
$ cd src/cs/CellSim
$ dotnet publish cellsim-macos.csproj -p:PublishProfile=Properties/PublishProfiles/osx-x64.pubxml
```

`Linux(x64)`の場合
```sh
cd src/cs/CellSim
dotnet publish cellsim-linux.csproj -p:PublishProfile=Properties/PublishProfiles/linux-x64.pubxml
```

`Linux(arm64)`の場合
```sh
cd src/cs/CellSim
dotnet publish cellsim-linux.csproj -p:PublishProfile=Properties/PublishProfiles/linux-arm64.pubxml
```

## 実行ファイルの場所
### C++の場合
`./build-scripts/build/bin/`に作られます。
MSVCでビルドされた場合は`./build-scripts/build/bin/Release/`に作られます。

### C#の場合
`./cs-publish/`に作られます。

# コマンドラインオプション
### `-b` `--binary`
実行結果を`.bin`ファイルとして出力します。
```sh
./cellsim -b
```
### `-c` `--csv`
実行結果を`.csv`ファイルとして出力します。
```sh
./cellsim -c
```
### `-h` `--help`
ヘルプを表示します。  
**注意:** このオプションはほかのオプションと併用できません。
```sh
./cellsim -h
```
### `-i` `--image`
実行結果を画像ファイルとして出力します。
```sh
./cellsim -i
```
### `-o` `--output`
実行結果の出力ディレクトリを指定します。  
**注意:** 指定しない場合は`./result/`になります。
```sh
./cellsim -b -i -o "./my-output-path"
```
```sh
./cellsim -b -i -o "./my-output-path/"
```
### `-p` `--param`
パラメータをオーバーライドします。
ここでは、細胞の初期数をオーバーライドしています。
```sh
./cellsim -b -p cell.cellCount=1000
```
複数のパラメータをオーバーライドすることもできます。
```sh
./cellsim -b -p cell.cellCount=3000 -p cellAlgorithm.useClusterModel=true
```
### `-s` `--setting`
使用する設定ファイルのパスを指定します。  
**注意:** 指定しない場合は`./config.json`が使われます。
```sh
./cellsim -b -s "./my-config.json"
```
### `-v` `--video`
実行結果を動画ファイルとして出力します。
```sh
./cellsim -v
```
### `--create-image`
出力したcsvファイルまたはbinファイルから画像を作成します。
このオプションは`-o` `--output`のみと併用可能です。  
**注意:** 指定しない場合は`./result/images/`になります。
```sh
./cellsim --create-image "./my-csvpath" -o "./my-image-path"
```
```sh
./cellsim --create-image "./my-csvpath/" -o "./my-image-path"
```
### `--create-video`
出力したcsvファイル、binファイル、画像ファイルから動画を作成します。
このオプションは`-o` `--output`のみと併用可能です。  
**注意:** 指定しない場合は`./result/out.mp4`になります。
```sh
./cellsim --create-image "./my-imagepath" -o "./my-video-path/my-video-name.mp4"
```
```sh
./cellsim --create-image "./my-imagepath/" -o "./my-video-path/my-video-name.mp4"
```
### `--named-pipe-in` 
GUIツールと通信するための、読み取り用の名前付きパイプの名前を指定します。
シミュレータは指定したパイプから情報を読み取ります。  
**注意:** このオプションは`--named-pipe-out`と併用する必要があります。
```sh
./cellsim --named-pipe-in "my-pipe-in" --named-pipe-out "my-pipe-out"
```
### `--named-pipe-out`
GUIツールと通信するための、書き込み用の名前付きパイプの名前を指定します。
シミュレータは指定したパイプに情報を書き込みます。  
**注意:** このオプションは`--named-pipe-in`と併用する必要があります。
```sh
./cellsim --named-pipe-in "my-pipe-in" --named-pipe-out "my-pipe-out"
```
### `--param-sweep`
パラメータ範囲を順番に実行します。
以下の例では細胞数を1000個から2000個まで100刻みで実行します。
```sh
./cellsim -b --param-sweep cell.cellCount=1000:2000:100
```