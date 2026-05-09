# Project-ProgImp3
notice README expliquant comment créer l’exécutable, principal, l’exécutable de la génération de fichiers des tests et
comment générer les fichiers de tests,
## explication

se programme permet de realiser des test sur l'algorithme des kpp-v.
il est construit de cette maniere:

- une interface graphique pour la visualisation
- une partie console pour les test repété en grand nombre ainsi que la comparaison de l'optimisation entre l'utilisation
  de liste et d'abre de recherche multi dimensionnel



## compilation 

pour compiler le programme principale utiliser

```bash
    make 
```

pour compiler le programme de generation de fichier

```bash
    make generator
```

## execution

pour executer le programme en interface graphique 

```bash
    ./main -i <fichier.txt>
```

pour executer le programme de generation de donnée

```bash
    ./generator <nb_point> <nb_dimension> <nb_classe> > <fichier_sauvegarde.txt>
```

pour lancer la generation de nouvelle donner de test

```bash
    ./generation.sh
```

pour lancer la generation des test 

```bash
    ./test.sh
```