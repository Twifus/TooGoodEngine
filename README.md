# TooGoodEngine
Projet de moteur physique pour le cours 8INF935 de l'UQAC par BABU Baptiste, CESARO Louis, FARINES Jean et ROYANT Yann.

# Dépendances
Le projet nécessite la bibliothèque SDL2. La bibliothèque pour Windows (format .dll) est fournie dans `external/SDL2-2.0.10`.

Il est aussi nécessaire d'avoir CMake (version 3.0 minimum) pour compiler le projet.

# Compilation et tests
## Linux
> cd build
> cmake ..
> make all test
> ./Game

## Windows
Vous pouvez ouvrir le projet sous VisualStudio pour le compiler avec CMake, et exécuter / débogguer le programme.

# Utilisation
Les arguments en ligne de commande n'ont pas pu étre implémentées à temps.
Trois projectiles sont tirés :
 - ROUGE : chute libre, masse = 1kg, damping = 1
 - VERT : tir à la verticale à 10m/s, masse = 3kg, damping = 0.7
 - BLEU : tir en cloche à vx = 10ms vy = 15ms, masse = 5kg, damping = 0.5

L'échelle de distance par défaut est de 100px pour 1m.

Pour quitter la fenêtre, cliquez sur la croix