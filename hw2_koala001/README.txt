AMATH483 hw2
Cynthia Hong

Overview
The following is the spec of my howework, including the detail of my
homework and the details of compilation(p6).

Part1: the details of compilation(p6)
run
```bash
g++ -
std = c++ 14 - c - fPIC hw2_koala001_p1_function.cpp;
g++ - std = c++ 14 - c - fPIC hw2_koala001_p2_function.cpp;
g++ - std = c++ 14 - c - fPIC hw2_koala001_p3_function.cpp;
g++ - std = c++ 14 - c - fPIC hw2_koala001_p4_function.cpp;
g++ - std = c++ 14 - c - fPIC hw2_koala001_p5_axpy_function.cpp;
g++ - std = c++ 14 - c - fPIC hw2_koala001_p5_gemv_function.cpp;
g++ - std = c++ 14 - c - fPIC hw2_koala001_p5_gemm_function.cpp;
```
```bash
g++ -
shared - o librefBLAS.so hw2_koala001_p1_function.o hw2_koala001_p2_function.o hw2_koala001_p3_function.o hw2_koala001_p4_function.o hw2_koala001_p5_axpy_function.o hw2_koala001_p5_gemv_function.o hw2_koala001_p5_gemm_function.o;
```
run
```bash
g++ -
std = c++ 14 - o hw2_main hw2_koala001_main.cpp - I.- L.- lrefBLAS
```
run
  ```bash
./
hw2__koala001_main
  ```

Part2: the output of each question
p1: output1.csv
p2: output2.csv
p3: output3.csv
p4: output4.csv
p5: output5_1.csv (axpy)
    output5_2.csv (gemm)
    output5_3.csv (gemv)

Part3: the name of function file
p1: hw2_koala001_p1_function.cpp
p2: hw2_koala001_p2_function.cpp
p3: hw2_koala001_p3_function.cpp
p4: hw2_koala001_p4_function.cpp
p5.1: hw2_koala001_p5_axpy_function.cpp
p5.2: hw2_koala001_p5_gemv_function.cpp
p5.3: hw2_koala001_p5_gemm_function.cpp
 
Part4: the name of header file
p1: hw2_koala001_p1_function.hpp
p2: hw2_koala001_p2_function.hpp
p3: hw2_koala001_p3_function.hpp
p4: hw2_koala001_p4_function.hpp
p5.1: hw2_koala001_p5_axpy_function.hpp
p5.2: hw2_koala001_p5_gemv_function.hpp
p5.3: hw2_koala001_p5_gemm_function.hpp
 
part5: other
main: hw2_koala001_main.cpp
shared library file: librefBLAS.so
plot: plot.pdf
extra credit: extra_credit_cynthia.pdf

