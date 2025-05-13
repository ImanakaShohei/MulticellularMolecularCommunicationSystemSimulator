#!/bin/bash

# "build" ディレクトリが存在する場合は削除（中身ごと）
if [ -d build ]; then
    echo "Deleting existing build directory..."
    rm -rf build
fi

# "build" ディレクトリを作成
echo "Creating build directory..."
mkdir build

# コンパイラにgccを指定する、と思っていたのか？
# cmake -S . -B build -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# コピー
cp ./resources/build.sh ./build/
cp ./resources/rebuild.sh ./build/

# "build" ディレクトリに移動
cd build

# cmake の初期構成を実行
echo "Running cmake .."
cmake ..

# Releaseビルドを実行
echo "Building in Release mode..."
cmake --build . --config Release
