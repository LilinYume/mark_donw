mark_donw
=========

memo

やる
 プレーンテキストの見た目を損なわない。
 行頭にスペース・タブを挿入して階層または、セクションを決める。
 行頭のspaceをそのままhtmlドキュメントで保つ
 見出しから目次を作る
 htmlとしてエスケープが必要 <>
 
 
やる？
 日付の変換 「今日」を "12月22日"にするなど



やり方を考える
 読み取り方　行単位？
 ファイル更新ヶ所のみhtmlタグを更新、またはファイル全体を更新しなおす。


マークダウンするやつ、ことばの定義とか。

space :
\	\t
\	' '

newline :
\	\n'

white space :
\	space
\	newline

mark :（行頭）
 見出し:
\  #（半角）space(<=0) moji newline
\ ＃（全角）space(<=0) moji newline
\   ■ space(<=0) moji newline
\   □ space(<=0) moji newline
\   ● space(<=0) moji newline
\   ○ space(<=0) moji newline

 区切り:　（行頭）
\   -----------　
   moji 
\   -----------

\   ==========
   moji
\   ==========

     --- === は10個以上連続
     またmojiは1行のみで上下に--- または ==== で挟まれる

 リスト: (行頭)
\   ・space(0) moji newline

 強調（ボルド）:（行中）
\    - moji - 
-(ハイフン)の前後には1個のspaceを左右に含む space - space moji ...
	space(1) - moji space(1) - opt newline

 イタリック体:（行中）
\    _ moji _ 
	_(アンダースコア)の前後には1個のspaceを左右に含む space _ space moji ...
	space(1) _ moji space(1) _ opt newline

 エスケープ文字（行中）
 　　\\

moji :
  エスケープされたmark
  漢字
  ひらがな
  カタカナ（全角）
  カタカナ（半角）
  記号
  数字

ヘッドライン以下のタブでインデントされた行をグルーブ化する

headline
\\t moji
\\t moji

区切り以下のリストをグルーブ化する

----------
moji
----------
\・space(0) moji newline
\・space(0) moji newline


mark の ネストについて

見出しの中にリスト・強調・イタリック体は含まない。
区切りは上下にあってもよい。

リストのメンバーにボルト、イタリック体を含むことができる。

ボルドとイタリック体は共存できる。

強調・イタリック体は行をまたぐこともある。
閉じられていないハイフン、アンダースコア行末（newline）で効果を失う


