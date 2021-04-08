# Linux Device Driver Features Example
A device driver where features are added step by step

## Compilation
Compile the module by running `make` in the `module` directory. The module is named `devicedriver.ko` and should be found in the `module` directory.

## Feature #1 - Loading and unloading module
To load the module run `insmod devicedriver.ko`. To unload the module run `rmmod devicedriver`. The output from the `printk()` function can be viewed by running `dmesg`.

## Feature #2 - Adding module information
It's possible to add module information such as which license applies, who's the author, a description and a version number. This information among other can be viewed by running `modinfo devicedriver.ko`.
