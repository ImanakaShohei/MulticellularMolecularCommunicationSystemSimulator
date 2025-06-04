# 準備中...
このページはまだ完成していません。  

# Overview
分子通信シミュレーションのための汎用シミュレータであり、ユーザがシミュレーションのパラメータや力学作用を定義することでさまざまなモデルに対応したシミュレーションを実行することができます。

# 動作要件
- C++20をサポートするコンパイラ
- CMake (version 3.11以降)
- Windows or macOS or Linux

# ビルド方法

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
ヘルプを表示します。このオプションはほかのオプションと併用できません。
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
指定しない場合は`./result/`になります。
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
指定しない場合は`./config.json`が使われます。
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
指定しない場合は`./result/images/`になります。
```sh
./cellsim --create-image "./my-csvpath" -o "./my-image-path"
```
```sh
./cellsim --create-image "./my-csvpath/" -o "./my-image-path"
```
### `--create-video`
出力したcsvファイル、binファイル、画像ファイルから動画を作成します。
このオプションは`-o` `--output`のみと併用可能です。
指定しない場合は`./result/out.mp4`になります。
```sh
./cellsim --create-image "./my-imagepath" -o "./my-video-path/my-video-name.mp4"
```
```sh
./cellsim --create-image "./my-imagepath/" -o "./my-video-path/my-video-name.mp4"
```