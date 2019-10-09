# TooGoodEngine
Projet de moteur physique pour le cours 8INF935 de l'UQAC par BABU Baptiste, CESARO Louis, FARINES Jean et ROYANT Yann.

# Dépendances
Le projet nécessite les bibliothèque SDL2 et SDL2_image. Les binaires Windows (format .dll) sont déjà fournis dans `external`.

Il est aussi nécessaire d'avoir CMake (version 3.0 minimum) pour compiler le projet.

# Compilation et tests
Sur système Unix
> cd build
> cmake ..
> make all test

ou bien utilisez un IDE supportant CMake

# Exécutables
Deux exécutables sont disponibles : Game et BlobScene

## Game
Un programme de démonstration des collisions simples et des ressorts. En lançant le programme `Game`, 
il est possible de taper '1' ou '2' puis appuyer sur 'Entrée' pour choisir un mode :
'1' - Demonstration de collisions simples entre trois particules.
'2' - Démonstration des divers générateurs de forces de ressorts

## Blob

Un programme de test faisant figurer le blob est disponible en lançant 
> ./BlobScene

Le blob peut être séparé en cliquant sur la souris puis réassemblé en cliquant à nouveau.
Les flèches directionnelles servent à se déplacer.

# Divers
L'échelle de distance par défaut est de 100px pour 1m.
Pour quitter la fenêtre, cliquez sur la croix