# Hello Gnome Extension

A simple 'Hello World' extension for Gnome. Made in **seconds** with help from artificial intelligence: [ChatGPT](https://openai.com/blog/chatgpt/).

## Installation

Clone this repository to any location in your filesystem (e.g. **~/Projects**), copy the files to extensions folder, restart gnome-shell and enable the extension.

```
cd ~/Projects && git clone --depth 1 git@github.com:jukkapajarinen/hello-gnome-extension.git;
cp -R ./hello-gnome-extension ~/.local/share/gnome-shell/extensions/hello-gnome-extension@jukkapajarinen.com;
killall -SIGQUIT gnome-shell;
gnome-extensions enable hello-gnome-extension@jukkapajarinen.com;
```
