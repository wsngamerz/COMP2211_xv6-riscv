# Getting started

## Setting up the build environment
for the first time do the following commands:

```sh
# get the build tools
singularity pull docker://callaghanmt/xv6-tools:buildx-latest
```

To load the build environment shell run:
```sh
# run the shell
singularity shell xv6-tools_buildx-latest.sif
```

## Building xv6
```sh
make
```

## Running xv6
```sh
make qemu
```

To exit from qemu you can use the following keyboard shortcut:
<kbd>Ctrl</kbd> + <kbd>A</kbd> and then press <kbd>x</kbd>
