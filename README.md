# whitakers-words-terminal
> a command line interface for the popular english-latin dictionary

This was originally a cute little C program that sent a GET request to [William Whitaker's Words](http://archives.nd.edu/words.html) for basic translation. It's now a slightly more powerful Python tool, but it works pretty much the same way. The original C program is still here as a historical curiosity but is essentially deprecated.

## usage
##### Python (new)
All you need to run the Python program is a standard Python 2 install. If you pass `latin.py` a Latin word (e.g. `-l salve`), it will simply translate and exit. If you pass it an English word (e.g. `-e hello`), it will do likewise. Otherwise, it will enter an interactive environment:
```
l 0:>
```
The prompt displays two things: the current translation mode (`l`, Latin to English, or `e`, English to Latin) and the entries setting (if multiple entries found, how many to display). Here, `0` indicates "show all entries." There's currently a bug where this only works for English translations.

Typing any word will attempt to translate it under the current settings. You can modify the settings by entering `:l` (switch to Latin), `:e` (switch to English), or `:3` (switch to 3 entries per term). Use your imagination for other entry display settings.

Issuing `:q`, `:quit`, `EOF` (usually `ctrl+D`), or a keyboard interrupt (usually `ctrl+C`) will quit the interactive mode. You can also use arrow keys to access command history within the same session.

##### C (old)
The `latin.c` program should compile fine as long as you have a normal `libc` installed somewhere. The syntax is simple:
```sh
$ latin <word>     # latin to english
$ latin -E <word>  # english to latin
```

##### general
If you intend on using it as a translation tool, I would recommend making it accessibly everywhere (e.g. by adding it to your `$PATH` environment variable), just so that it's a little more convenient to use.

## caveats
This program simply makes a request to the Notre Dame servers for the translation, so it obviously won't work without Internet access. Please don't spam their servers. Rewriting the original WORDS program in Python to run locally is too monumental a task right now.
