#!/usr/bin/env bash

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"

make -C "$PROJECT_DIR" > /dev/null
make -C "$PROJECT_DIR" generator > /dev/null

mkdir -p "$PROJECT_DIR/test_console"


"$PROJECT_DIR/generator" 10000 10 5 > "$PROJECT_DIR/test_console/data_for_k.txt"




"$PROJECT_DIR/generator" 10000 2   5 > "$PROJECT_DIR/test_console/data_dim_2.txt"
"$PROJECT_DIR/generator" 10000 10  5 > "$PROJECT_DIR/test_console/data_dim_10.txt"
"$PROJECT_DIR/generator" 10000 20  5 > "$PROJECT_DIR/test_console/data_dim_20.txt"
"$PROJECT_DIR/generator" 10000 30  5 > "$PROJECT_DIR/test_console/data_dim_30.txt"
"$PROJECT_DIR/generator" 10000 40  5 > "$PROJECT_DIR/test_console/data_dim_40.txt"
"$PROJECT_DIR/generator" 10000 60  5 > "$PROJECT_DIR/test_console/data_dim_60.txt"
"$PROJECT_DIR/generator" 10000 70  5 > "$PROJECT_DIR/test_console/data_dim_70.txt"
"$PROJECT_DIR/generator" 10000 80  5 > "$PROJECT_DIR/test_console/data_dim_80.txt"
"$PROJECT_DIR/generator" 10000 90  5 > "$PROJECT_DIR/test_console/data_dim_90.txt"
"$PROJECT_DIR/generator" 10000 95  5 > "$PROJECT_DIR/test_console/data_dim_95.txt"
"$PROJECT_DIR/generator" 10000 100 5 > "$PROJECT_DIR/test_console/data_dim_100.txt"





"$PROJECT_DIR/generator" 10      10 5 > "$PROJECT_DIR/test_console/data_nb_10.txt"
"$PROJECT_DIR/generator" 30      10 5 > "$PROJECT_DIR/test_console/data_nb_30.txt"
"$PROJECT_DIR/generator" 100     10 5 > "$PROJECT_DIR/test_console/data_nb_100.txt"
"$PROJECT_DIR/generator" 300     10 5 > "$PROJECT_DIR/test_console/data_nb_300.txt"
"$PROJECT_DIR/generator" 1000    10 5 > "$PROJECT_DIR/test_console/data_nb_1000.txt"
"$PROJECT_DIR/generator" 3000    10 5 > "$PROJECT_DIR/test_console/data_nb_3000.txt"
"$PROJECT_DIR/generator" 10000   10 5 > "$PROJECT_DIR/test_console/data_nb_10000.txt"
"$PROJECT_DIR/generator" 30000   10 5 > "$PROJECT_DIR/test_console/data_nb_30000.txt"
"$PROJECT_DIR/generator" 100000  10 5 > "$PROJECT_DIR/test_console/data_nb_100000.txt"
"$PROJECT_DIR/generator" 300000  10 5 > "$PROJECT_DIR/test_console/data_nb_300000.txt"
"$PROJECT_DIR/generator" 1000000 10 5 > "$PROJECT_DIR/test_console/data_nb_1000000.txt"

echo "generation terminee./"
