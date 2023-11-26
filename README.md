
- [readline](#readline-関数-)
- rl_clear_history
- rl_on_new_line
- rl_replace_line
- rl_redisplay
- [add_history](#-addhistory-関数)
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


# ⭐️`readline` 関数 

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


# ⭐️ add_history 関数

### 関数原型
```c
Copy code
#include <readline/readline.h>
#include <readline/history.h>

void add_history (char *string);

```

### 用途
char *stringを履歴リストに追加します。このように追加された文字列は、readlineで方向キーを使用して確認することができます。