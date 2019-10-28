#   Make:
Makefile 位于bin文件夹中，在bin下执行 `make splc`将会得到一个可执行文件splc

#   sqlc
这个可执行文件的解析结果将会输出到控制台的stdout上。

#   sqlc.py
这个脚本可以读取参数并以其为代码路径运行sqlc, 并将结果输出到代码文件同路径下的.out文件中。同时也支持不带参数运行，脚本运行后可以通过输入文件路径的方式解析代码文件，结果同样会输出到代码文件同路径下的.out文件中。例如：
```bash
python3 splc.py ../test/test_1_o04.spl 
```

