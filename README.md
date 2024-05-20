# Internet Cafe
Small application that registers users in internet cafe.

## Build & Run
```sh
$ cmake -S . -B build
$ cd build
$ make
$ ./internet_cafe <input_file>
```

## Testing
All tests input are in resources file. You need to check outputs with given
```sh
$ cd build
$ make
$ ./internet_cafe resources/in1.txt
# check output with resources/out1.txt
$ ./internet_cafe resources/in2.txt
# check output with resources/out2.txt
```
