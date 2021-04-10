# Linux Device Driver Features Example
A device driver where features are added step by step

## Compilation
Compile the module by running `make` in the `module` directory. The module is named `devicedriver.ko` and should be found in the `module` directory.

Compile the user space application by running `make` in the `user space application` directory. The application is named `app` and should be found in the `user space application` directory.

## Feature #1 - Loading and unloading module
To load the module run `insmod devicedriver.ko`. To unload the module run `rmmod devicedriver`. The output from the `printk()` function can be viewed by running `dmesg`.

## Feature #2 - Adding module information
It's possible to add module information such as which license applies, who's the author, a description and a version number. This information among other can be viewed by running `modinfo devicedriver.ko`.

## Feature #3 - Passing arguments to module
One can pass arguments when loading a module. If there is an argument named `size` it can be passed like this: `insmod devicedriver.ko size=4`. This value can also be read and written to at run-time after loading the module. The path to read/write would then be `/sys/module/devicedriver/parameters/size`. `modinfo devicedriver.ko` also lists the modules available parameters with descriptions and data types.

## Feature #4 - Module parameter with a callback
This is the same as Feature #3 with the addtional feature of being able to react to changes written to the parameter at run-time. It's possible to reimplement the getter and setter method.

## Feature #5 - Dynamically allocate major and minor ID
The major ID identifies the general class of device, and is used by the kernel to look up the appropriate driver for this type of device. The minor ID uniquely identifies a particular device within a general class, as there might be several devices using the same driver.
