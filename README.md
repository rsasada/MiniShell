- [readline](#readline-関数)
- rl_clear_history
- rl_on_new_line
- rl_replace_line
- rl_redisplay
- [add_history](#addhistory-関数-)
- isatty
- ttyname
- ttyslot
- ioctl
- tcsetattr
- tcgetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr


# `readline` 関数

## 関数原型

```c
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);
```

### 用途

readlineは、char *promptをターミナルに表示し、ターミナルから入力された文字列を返します。

### 引数

出力する文字列

### 戻り値

- 入力された文字列を返します。改行は削除されます。
- 空の文字列の場合は、空の文字列を返します。
- 何も読み取れない場合は、NULLを返します。（EOF）

### その他

readline内部でerrnoが設定されます。例えば、ヘッダーファイルが正しく設定されていない場合、errno=2が設定され、問題がない場合はerrno=0になります。

- reference : https://qiita.com/keitean/items/7c77f501eab5440e9200

# add_history 関数 

## 関数原型

```c
#include <readline/history.h>

int add_history(const char *line);
```

### 引数

*line : 追加する文字列

### 機能

以前に入力した文字列をキーボードの上下ボタンを使用して再呼び出すことができるが、このような文字列が保存された履歴に line 文字列を追加します。

### 戻り値

- 成功時：0
- エラー時：-1

### 注意事項
UNIXのビルトイン read_line を使用する場合はint型を返しますが、GNUライブラリの read_line を使用する場合は戻り値がありません。





