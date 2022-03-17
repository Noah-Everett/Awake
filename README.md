# **Awake**
Application to keep mac awake while in clam shell mode (like [Amphetamine](https://www.google.com/search?q=amphetimine+app+store&rlz=1C5CHFA_enUS996US996&oq=amphetimine+app+store&aqs=chrome..69i57.3334j0j7&sourceid=chrome&ie=UTF-8#:~:text=Amphetamine%20on%20the,com%20%E2%80%BA%20app%20%E2%80%BA%20amphetamine)). Built for new MacBook Pros (from 2021) which, for some reason, don't allow Amphetamine to work.

(README syntax: `[]` denotes an optional argument, `<>` denotes a required argument)

## **Installation**
To install Awake you will need [CMake](https://cmake.org/). I recommend installing CMake via [Homebrew](https://brew.sh/). After installing the dependencies, the project repository can be downloaded via `git clone` or manually, then Awake and can be built and installed via CMake.

Install Homebrew: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

Install CMake: `brew install [--cask] cmake`

Clone the repository: `cd </dir/to/put/Awake/>` & `git clone -b <version name> [--depth 1] https://github.com/Noah-Everett/Awake` or download the latest release from [here](https://github.com/Noah-Everett/Awake/releases). Then ``.

Build Awake: `cd <Awake/>` & `mkdir build && cd build` & `cmake -S ../ -B ./ -DCMAKE_INSTALL_PREFIX=~/.local/bin` & `make`

Install Awake: `make install` (puts `awake` executable in `~/.local/bin` or wherever else `-DCMAKE_INSTALL_PREFIX` is set to)

Set the `PASSWORD` environment variable: `echo 'export PASSWORD="<password used for sudo>"' >> ~/.zshrc`. 

You're done! Awake is installed and should be runnable from any directory. 

## **Usage**
To run Awake you can run `awake` from any directory in the terminal. For help statement run `awake -h` or `awake --help`.

If running `awake` results in `PUT ERROR HERE`, make sure the `PASSWORD` environmental variable is set. (Example: put `export $PASSWORD="xx##"` in `~/.zshrc`)