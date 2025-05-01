@echo off
rem "build"フォルダがあれば削除（中身も含めて）
if exist build (
    echo Deleting existing build directory...
    rmdir /s /q build
)

rem "build"フォルダを作成
echo Creating build directory...
mkdir build

rem "バッチファイルをコピー"
copy .\resources\build.bat .\build
copy .\resources\rebuild.bat .\build

rem "build"フォルダに移動
cd build

rem CMakeの初期構成を実行
echo Running cmake ..
cmake ..

rem Releaseビルドを実行
echo Building in Release mode...
cmake --build . --config Release

pause