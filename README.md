# TooGoodEngine
Projet de moteur physique pour le cours 8INF935 de l'UQAC par BABU Baptiste, CESARO Louis, FARINES Jean et ROYANT Yann.

# Dépendances
Le projet nécessite les bibliothèque SDL2, SDL2_image, GLEW et OpenGL. Les binaires pour Windows (format .dll) sont déjà fournis dans `external`.

Il est aussi nécessaire d'avoir CMake (version 3.0 minimum) pour compiler le projet.

# Compilation et tests
Sur système Unix
> cd build
> cmake ..
> make

ou bien utilisez un IDE supportant CMake

# Exécutable
L'executable du jalon 4 est nommé ContactScene
Il peut être lancé sur les systèmes Unix avec la commande
> ./ContactScene
ou en double-cliquant sur l'executable (Windows)

On peut y observer un cube lancé contre un mur avec des vitesses linéaire et angulaire non nulles.
La simulation s'arrête une fois le cube rentré en contact avec le mur, et affiche les points de contact. 
