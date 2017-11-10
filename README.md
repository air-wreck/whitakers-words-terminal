# whitakers-words-terminal
a command line interface for the popular english-latin dictionary

I wanted to learn a little about making web requests from C using sockets, so I made this. The program simply sends an HTTP GET request to [William Whitaker's Words](http://archives.nd.edu/words.html) and then prints out the result. Maybe I'll add some fancier features in the future.

## usage
To use it on Linux or OS X, all you need to do is clone the repository and run the build script (which is kind of unnecessary, but oh well). If you're on Windows, you're on your own.
```shell
git clone http://github.com/air-wreck/whitakers-words-terminal
cd whitakers-words-terminal
./build.sh
```

If you intend on using it as a translation tool, I would recommend making it accessibly everywhere (e.g. by adding it to your PATH environment variable), just so that it's a little more convenient to use. The syntax is simple:
```shell
./latin <word>     # latin to english
./latin -E <word>  # english to latin
```
