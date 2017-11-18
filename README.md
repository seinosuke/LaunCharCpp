# LaunChar
タイピングするたび画面に文字が飛び出すデスクトップアクセサリ  
各キーにピアノやドラムなどの音を割り当てた版  

![sample.png](https://sites.google.com/site/fileupupup/cabinet/launchar_sample.png)

## 動作環境
Windows10での動作を確認しました。  
Windows7では背景の透過処理が行われないという問題が発生しており、現在原因を調査中です。  

また、実行には DirectX のランタイムが必要となります。  
「コンピューターにd3dx9_43.dllがないため、プログラムを開始できません。  
この問題を解決するには、プログラムを再インストールしてみてください。」  
というエラーが発生する場合は  

[https://www.microsoft.com/ja-jp/download/details.aspx?id=35&](https://www.microsoft.com/ja-jp/download/details.aspx?id=35&)  

からDirectXエンドユーザーランタイムWebインストーラ dxwebsetup.exe をダウンロードしてインストールを行ってください。

![d3dx9.png](https://sites.google.com/site/fileupupup/cabinet/d3dx9_43dll.png)

## ダウンロード

[LaunChar.zip](https://github.com/seinosuke/LaunCharCpp/releases/download/0.1.0/LaunChar.zip)

## 使い方

LaunChar.exe を起動するだけです。他のウィンドウで作業をしていると、キーボードで打った文字が画面上に飛び出してきます。  

タスクバーや[Alt]+[Tab]などでLaunCharウィンドウをアクティブにし特定のキーを入力することで、文字のジャンプ力やキーの音の切り替えなどができます。

* [Alt] + [M] : キーの入力音切り替え  
* [Alt] + [J] : 文字のジャンプ力切り替え  
* [Alt] + [Q] : アプリケーションを終了  

## クレジット

ピアノ音やドラム音などのwavファイル群はフリー音楽素材 [魔王魂さま](http://maoudamashii.jokersounds.com) のものを使用しています。  
（魔王魂素材利用規約 [https://maoudamashii.jokersounds.com/music_rule.html](https://maoudamashii.jokersounds.com/music_rule.html)）  

## ライセンス

[MIT License](https://opensource.org/licenses/MIT)
