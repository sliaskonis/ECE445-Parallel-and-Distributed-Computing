Compile:
-all
    make
-ask2 for question A. with -DAQ flag , for question B. with -DBQ flag and change the -DLEVEL for the collapse level you want
    gcc -fopenmp -g -I/usr/local/opt/libomp/include/ -L/usr/local/opt/libomp/lib/ -DBQ -DLEVEL=2 src/ask2_par.c -o bin/ask2_par

-ask2 with x
Run: Executables created inside ./bin/
    ./bin/<exec_name>