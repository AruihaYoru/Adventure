# Adventure Revisited - WebAssembly Port

![WebAssembly](https://img.shields.io/badge/WebAssembly-654FF0?style=for-the-badge&logo=webassembly&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![HTML5 Canvas](https://img.shields.io/badge/HTML5_Canvas-E34F26?style=for-the-badge&logo=html5&logoColor=white)

このプロジェクトは、Atari 2600の伝説的ゲーム「**Adventure**」（1980年、Warren Robinett作）のC++移植版である「**Adventure Revisited**」（Peter Hirschberg作）をベースに、**WebAssembly (WASM)** へ移植したプロジェクトです。ブラウザ上でプラグインなしで軽快に動作します。

## 主な機能

- **ブラウザネイティブ動作**: C++のロジックをEmscriptenでWASMにコンパイルし、HTML5 Canvas + JavaScriptで動作。
- **ピクセルパーフェクトレンダリング**: CSSの `image-rendering: pixelated;` とCanvasを活用し、レトロなドット絵をシャープに描画。
- **Web Audio API**: 音声処理はブラウザのWeb Audio APIに委譲し、快適でシームレスなサウンド再生を実現。
- **イースターエッグ対応**: オリジナルに忠実な隠し部屋への到達をJS側で検知・UI連動。
- **ピースフル・エディション**: 蝙蝠とドラゴン）が出現しない特別なモードを搭載（コンパイルオプションで切り替え可能）。
- **グローバル変数**: ....どうせ、こんなゲームを搭載するときは例のイースターエッグを使いたいときがほとんどでしょうし、イースターエッグの隠し部屋に入ると`window.crystal_key`が1になります。（レディープレイヤー１ネタ）

## 遊び方

| 操作 | アクション |
|---|---|
| **矢印キー (Arrows)** | キャラクターの移動 |
| **スペース (Space)** | アイテムを拾う / 置く |
| **Enter** | ゲームレベルの選択 (1〜3) |
| **R** | リセット |

## ビルド方法

このゲームをビルドするには、[Emscripten (emsdk)](https://emscripten.org/) がインストールされた環境が必要です。
ソースコードのディレクトリ (`winadventure/sourcecode/wasm_source/`) に移動し、以下のコマンドを実行してください。

### 通常版
```cmd
emcc main.cpp Adventure.cpp -o adventure.js -s EXPORTED_RUNTIME_METHODS="[\"ccall\", \"cwrap\"]" -s EXPORTED_FUNCTIONS="[\"_main\", \"_set_key\", \"_get_screen_buffer\"]" -O3
```

### ピースフル・エディション
蝙蝠とドラゴンが無効化された平和なバージョンです。
以下のコマンドを手動で実行します（Windowsの場合は `\"` でエスケープ）。
```cmd
emcc main.cpp Adventure.cpp -o adventure_peaceful.js -s EXPORTED_RUNTIME_METHODS="[\"ccall\", \"cwrap\"]" -s EXPORTED_FUNCTIONS="[\"_main\", \"_set_key\", \"_get_screen_buffer\"]" -O3 -DPEACEFUL_MODE
```

## ディレクトリ構成

- `winadventure/sourcecode/wasm_source/`
  - `Adventure.cpp`, `main.cpp`: ゲームロジック (C++)
  - `index.html`: 通常版のエントリーポイント
  - `peaceful.html`: ピースフル版のエントリーポイント
  - `sounds/`: 効果音ファイル郡

## クレジット

- **Original Adventure for Atari 2600 (1980)**: Written by Warren Robinett for Atari.
- **Adventure Revisited (C++ Port)**: Copyright © 2006 Peter Hirschberg.
- **WASM Port & Modifications**: Aruiha (And assistance via AI).
