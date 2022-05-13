# **Awake**
Application to keep Mac awake while in clamshell mode (like [Amphetamine](https://www.google.com/search?q=amphetimine+app+store&rlz=1C5CHFA_enUS996US996&oq=amphetimine+app+store&aqs=chrome..69i57.3334j0j7&sourceid=chrome&ie=UTF-8#:~:text=Amphetamine%20on%20the,com%20%E2%80%BA%20app%20%E2%80%BA%20amphetamine)). Built for new MacBook Pros (from 2021) which, for some reason, don't allow Amphetamine to work.

(README syntax: `[]` denotes an optional argument, `<>` denotes a required argument)

## **Installation**
To install Awake you will need [CMake](https://cmake.org/). I recommend installing CMake via [Homebrew](https://brew.sh/). After installing the dependencies, the project repository can be downloaded via `git clone` or manually, then Awake and can be built and installed via CMake.

Install Homebrew: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

Install CMake: `brew install [--cask] cmake`

Get source code: `cd </dir/to/put/Awake/>` & `git clone -b <version name> [--depth 1] https://github.com/Noah-Everett/Awake` or download the latest release from [here](https://github.com/Noah-Everett/Awake/releases)

Build Awake: `cd <Awake/>` & `mkdir build && cd build` & `cmake -S ../ -B ./ -DCMAKE_INSTALL_PREFIX=~/.local` & `make`

Install Awake: `make install` (puts `awake` executable in `~/.local/bin` or wherever else `-DCMAKE_INSTALL_PREFIX` is set to)

Set the `PASSWORD` environment variable: `echo 'export PASSWORD="<password used for sudo>"' >> ~/.zshrc` & `source ~/.zshrc` 

You're done! Awake should be installed and runnable in the terminal. 

## **Setup Shortcut**
- Open `Shortcuts` (should already be on your Mac) 
- Click the `+` in the top of the window
- In the top left of the window, set the shortcuts name to be "Awake"
- In the search bar on the right, search for "Terminal" and double click on "Run Shell Script"
- In the "Run Shell Script" window, change the `echo "Hello World"` to `<awake installation location (~/.local/bin)>/awake -p <system password for sudo>`
- If you wish to pin shortcut in menu bar or make a keyboard shortcut, click the sliding bars button in the upper right and check the "Pin in Menu Bar" box or click the "Add Keyboard Shortcut" button to set a keyboard shortcut (recommended keyboard shortcut: ⌥⌘A)

You're done! Everything should be setup.

## **Usage**

#### Terminal
To run Awake, you can run `awake` from any directory in the terminal (if `awake` is installed in `~/.local/bin`). For a help statement run `awake -h` or `awake --help`.

If running `awake` results in `zsh: segmentation fault  awake`, make sure the `PASSWORD` environmental variable is set (`~/.zshrc` should contain `export $PASSWORD="<password used for sudo>"`).

#### Shortcut
To run the `Awake` shortcut, simply run the shortcut by either using a keyboard shortcut, through the menu bar, or in the `Shortcut` app. The program will terminate when the Mac stops charging or after 5 minutes of running. 

NOTE: If the Mac was not charging when program was started the program will stop itself.