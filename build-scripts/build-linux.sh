#!/bin/bash

# "build" ディレクトリが存在する場合は削除（中身ごと）
if [ -d build ]; then
    echo "Deleting existing build directory..."
    rm -rf build
fi

# "build" ディレクトリを作成
echo "Creating build directory..."
mkdir build

# コピー
cp ../src/resources/build.sh ./build/
cp ../src/resources/rebuild.sh ./build/

# "build" ディレクトリに移動
cd build

# cmake の初期構成を実行
echo "Running cmake .."
cmake -S ../.. -B . -DCMAKE_BUILD_TYPE=Release

# Releaseビルドを実行
echo "Building in Release mode..."
cmake --build . --config Release