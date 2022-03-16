# **Awake**
Application to keep mac awake while in clam shell mode (like [Amphetamine](https://www.google.com/search?q=amphetimine+app+store&rlz=1C5CHFA_enUS996US996&oq=amphetimine+app+store&aqs=chrome..69i57.3334j0j7&sourceid=chrome&ie=UTF-8#:~:text=Amphetamine%20on%20the,com%20%E2%80%BA%20app%20%E2%80%BA%20amphetamine)). Built for new MacBook Pros (from 2021) which, for some reason, dont allow Amphetimine to work.

## **Usage**
To install Awake you will need [CMake](https://cmake.org/). I recommend installing CMake via [Homebrew](https://brew.sh/). After installing the dependencies, the project repo can be downloaded via `git clone` and can be built and installed via CMake.

Installing Homebrew: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`

Installing CMake: `brew install --cask cmake`

Git clone Awake repo: `cd /Awake/src/dir/` & `git clone -b <version name> --depth 1 https://github.com/Noah-Everett/Awake`

Build Awake `mkdir build && cd build` & `cmake -S ../ -B ./ -DCMAKE_INSTALL_PREFIX=~/.local/bin` & `make`

Install Awake `make install`

You're done! Awake is installed and should be runnable from any directory. (run `awake`)