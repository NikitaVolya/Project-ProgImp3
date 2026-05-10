#!/usr/bin/env bash


PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
MAIN="$PROJECT_DIR/main"
DATA="$PROJECT_DIR/test_console"
RESULTS="$PROJECT_DIR/results"

rm -rf "$RESULTS"
mkdir -p "$RESULTS/vary_k"
mkdir -p "$RESULTS/vary_dim"
mkdir -p "$RESULTS/vary_nb_points"

echo "temps k"         > "$RESULTS/vary_k/save_tree.txt"
echo "temps k"         > "$RESULTS/vary_k/save_list.txt"
echo "temps dimension" > "$RESULTS/vary_dim/save_tree.txt"
echo "temps dimension" > "$RESULTS/vary_dim/save_list.txt"
echo "temps nb_points" > "$RESULTS/vary_nb_points/save_tree.txt"
echo "temps nb_points" > "$RESULTS/vary_nb_points/save_list.txt"



for k in 1 3 5 10 20 30 40 60 70 80 90 95 100; do
    (cd "$RESULTS/vary_k" && "$MAIN" -t "$DATA/data_for_k.txt" k "$k")
    (cd "$RESULTS/vary_k" && "$MAIN" -t "$DATA/data_for_k.txt" k "$k")
    (cd "$RESULTS/vary_k" && "$MAIN" -t "$DATA/data_for_k.txt" k "$k")
done


for dim in 2 10 20 30 40 60 70 80 90 95 100; do
    (cd "$RESULTS/vary_dim" && "$MAIN" -t "$DATA/data_dim_$dim.txt" d 10)
    (cd "$RESULTS/vary_dim" && "$MAIN" -t "$DATA/data_dim_$dim.txt" d 10)
    (cd "$RESULTS/vary_dim" && "$MAIN" -t "$DATA/data_dim_$dim.txt" d 10)
done



for nb in 10 30 100 300 1000 3000 10000 30000 100000 300000 1000000; do
    (cd "$RESULTS/vary_nb_points" && "$MAIN" -t "$DATA/data_nb_$nb.txt" p 10)
    (cd "$RESULTS/vary_nb_points" && "$MAIN" -t "$DATA/data_nb_$nb.txt" p 10)
    (cd "$RESULTS/vary_nb_points" && "$MAIN" -t "$DATA/data_nb_$nb.txt" p 10)
done



python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_k/save_list.txt"         "$RESULTS/vary_k/save_tree.txt"         "$RESULTS/vary_k/graph.svg"
python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_dim/save_list.txt"       "$RESULTS/vary_dim/save_tree.txt"       "$RESULTS/vary_dim/graph.svg"
python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_nb_points/save_list.txt" "$RESULTS/vary_nb_points/save_tree.txt" "$RESULTS/vary_nb_points/graph.svg"

echo "test fini"
