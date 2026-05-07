#!/usr/bin/env bash

PROJECT_DIR="$(cd "$(dirname "$0")" && pwd)"
MAIN="$PROJECT_DIR/main"
GENERATOR="$PROJECT_DIR/generator"
RESULTS="$PROJECT_DIR/results"


K_FIX=10
DIM_FIX=10
NB_POINTS_FIX=10000
NB_CLASSES=5


NB_POINTS_LIST=(10 10 10 30 30 30 100 100 100 300 300 300 1000 1000 1000 3000 3000 3000 10000 10000 10000 30000 30000 30000 100000 100000 100000 300000 300000 300000 1000000 1000000 1000000)
DIM_LIST=(2 2 2 10 10 10 20 20 20 30 30 30 40 40 40 60 60 60 70 70 70 80 80 80 90 90 90 95 95 95 100 100 100)
K_LIST=(1 1 1 3 3 3 5 5 5 10 10 10 20 20 20 30 30 30 40 40 40 60 60 60 70 70 70 80 80 80 90 90 90 95 95 95 100 100 100)


echo "debut de la generation des test ..."
make -C "$PROJECT_DIR" > /dev/null
make -C "$PROJECT_DIR" generator > /dev/null

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

TMPDATA=$(mktemp /tmp/data_XXXXXX.txt)
rm -f $TMPDATA EXIT


"$GENERATOR" "$NB_POINTS_FIX" "$DIM_FIX" "$NB_CLASSES" > "$TMPDATA"



for k in "${K_LIST[@]}"; do
    if [ "$k" -gt "$NB_POINTS_FIX" ]; then
        continue
    fi
    (cd "$RESULTS/vary_k" && "$MAIN" -t "$TMPDATA" k "$k")
done



for dim in "${DIM_LIST[@]}"; do
    "$GENERATOR" "$NB_POINTS_FIX" "$dim" "$NB_CLASSES" > "$TMPDATA"
    (cd "$RESULTS/vary_dim" && "$MAIN" -t "$TMPDATA" d "$K_FIX")
done



for nb in "${NB_POINTS_LIST[@]}"; do
    if [ "$K_FIX" -gt "$nb" ]; then
        continue
    fi
    "$GENERATOR" "$nb" "$DIM_FIX" "$NB_CLASSES" > "$TMPDATA"
    (cd "$RESULTS/vary_nb_points" && "$MAIN" -t "$TMPDATA" p "$K_FIX")
done


echo "generation des graphique "


python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_k/save_tree.txt"        "$RESULTS/vary_k/graph_tree.svg"
python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_k/save_list.txt"        "$RESULTS/vary_k/graph_list.svg"

python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_dim/save_tree.txt"      "$RESULTS/vary_dim/graph_tree.svg"
python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_dim/save_list.txt"      "$RESULTS/vary_dim/graph_list.svg"

python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_nb_points/save_tree.txt" "$RESULTS/vary_nb_points/graph_tree.svg"
python3 "$PROJECT_DIR/graphique.py" "$RESULTS/vary_nb_points/save_list.txt" "$RESULTS/vary_nb_points/graph_list.svg"

echo "test fini"

