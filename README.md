# Génération de Labyrinthes en C

Ce projet implémente un générateur de labyrinthes en C utilisant l'algorithme de Prim pour construire des arbres couvrants minimaux. Il fait partie du projet IN101 sur la génération de labyrinthes.

## Description

Le projet utilise l'algorithme de Prim pour générer des labyrinthes à partir de cartes avec des coûts d'arêtes. L'algorithme trouve l'arbre couvrant minimal d'un graphe représentant une grille, créant ainsi un labyrinthe sans cycles.

## Structure du Projet

```
├── include/           # Fichiers d'en-tête (.h)
│   ├── heap.h        # Structure de tas binaire
│   ├── map.h         # Structures de carte et d'arêtes
│   ├── maze.h        # Structure de labyrinthe
│   └── prim.h        # Algorithme de Prim
├── src/              # Code source (.c)
│   ├── app-generate-maze.c  # Application principale
│   ├── heap.c        # Implémentation du tas
│   ├── map.c         # Gestion des cartes
│   ├── maze.c        # Génération d'images de labyrinthes
│   ├── prim.c        # Algorithme de Prim
│   └── loader.c      # Chargement de fichiers
├── tests/            # Tests unitaires
├── data/             # Fichiers de données d'exemple
├── scripts/          # Scripts Python pour l'analyse
└── conf/             # Configuration Doxygen
```

## Fonctionnalités Principales

### Structures de Données
- **Map** : Représente une grille avec des coûts d'arêtes
- **Maze** : Contient l'arbre couvrant minimal résultant
- **Heap** : Tas binaire pour l'optimisation de l'algorithme
- **Neighbors** : Gestion des voisins d'un nœud

### Algorithmes
- **Algorithme de Prim** : Génération d'arbres couvrants minimaux
- **Tas binaire** : Structure de données pour l'optimisation
- **Génération d'images** : Export visuel des labyrinthes

## Compilation

Le projet utilise un Makefile pour la compilation. Commandes principales :

```bash
# Compiler tous les programmes
make compile-all

# Compiler l'application principale
make app-generate-maze

# Lancer tous les tests
make launch-tests

# Vérifier la syntaxe
make check-syntax

# Nettoyer les fichiers compilés
make clean

# Générer la documentation
make doc
```

## Utilisation

### Génération de Labyrinthe

```bash
# Compiler l'application
make app-generate-maze

# Générer un labyrinthe à partir d'un fichier de carte
./app-generate-maze data/map_10_8_42.txt
```

### Format des Fichiers de Carte

Les fichiers de carte suivent ce format :
```
largeur hauteur
coût_arête_bas coût_arête_droite
...
```

Exemple (`data/map_2_3_42.txt`) :
```
2 3
0 -14
-19 -19
18 -8
0 1
3 -5
3 14
```

## Tests

Le projet inclut plusieurs tests unitaires :

- `test-loader` : Test du chargement de fichiers
- `test-find-neighbors` : Test de recherche de voisins
- `test-prim` : Test de l'algorithme de Prim
- `test-heap-correctness` : Test de la correction du tas
- `test-heap-complexity` : Test de complexité du tas

```bash
# Lancer tous les tests
make launch-tests

# Compiler et lancer un test spécifique
make test-prim
./test-prim --all
```

## Analyse de Performance

Le projet inclut des outils d'analyse de performance :

```bash
# Test de complexité du tas
make test-heap-complexity
./test-heap-complexity

# Analyse avec Python
python scripts/plot_heap_complexity.py
```

## Documentation

La documentation est générée avec Doxygen :

```bash
make doc
```

La documentation sera disponible dans le dossier `doc/`.

## Options de Compilation

Le Makefile supporte plusieurs options :

- `DEBUG=1` : Active le mode debug
- `OPT=1` : Active les optimisations (-O3 -flto)
- `NOGUI=1` : Désactive l'interface graphique

Exemple :
```bash
make app-generate-maze DEBUG=1 OPT=1
```

## Dépendances

- **Compilateur** : GCC avec support C99
- **Bibliothèques** : libm (mathématiques)
- **Documentation** : Doxygen (optionnel)
- **Analyse** : Python avec matplotlib (optionnel)

## Auteur

Projet développé dans le cadre du cours IN101-TCS1 sur la génération de labyrinthes.

## Licence

Ce projet est développé à des fins éducatives dans le cadre du cours IN101.
