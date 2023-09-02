# BIM

Bonjour, notre projet est une application simplifiée de banque.
Lorsque vous lancez le serveur, une application pour le "banquier" est ouverte, elle sert à rechercher les informations d'un compte ou celle d'un client en passant l'ID de celui-ci.
Lorsque vous lancez le client, vous pouvez choisir votre agence et vous connectez ou vous inscrire.
Si vous vous connectez dans une mauvaise agence vous êtes automatiquement redirigé vers la bonne agence et vous êtes connecté .
Quand vous êtes connecté vous arrivez sur une page où figure tous vos comptes. En cliquant sur un de vos comptes vous obtenez les informations de celui-ci (id du compte, type de compte, solde, intérêt et historique des transactions)
La banque centrale se met à jour toutes les 20 secondes et les intérêts toutes les minutes.

Dans la suite de ce readme vous trouverez les instructions pour installer les outils nécessaires au fonctionnement du projet ainsi que les instructions du lancement du projet.


## Installation

Pour installer notre projet voici les étapes à suivre:
1. Télécharger et installer VCPKG
   [https://vcpkg.io/en/getting-started.html](https://vcpkg.io/en/getting-started.html "https://vcpkg.io/en/getting-started.html")
2. Suivre les instructions de VCPKG
3. Installer les trois librairies:
   -vcpkg install boost --triplet x64-windows
   -vcpkg install wxWidgets --triplet x64-windows
   -vcpkg install sqlite3 --triplet x64-windows
>Ces lignes sont pour le compilateur msvc
   4. Rajouter la ligne ci-dessous dans les options de lancement de cmake
      ```
       -DCMAKE_TOOLCHAIN_FILE="[PATH TO VCPKG]/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET="x64-windows"
      ```


## Lancement du projet

Dans BIM il y a deux dossiers, un **serveur** et un **client**,
pour lancer notre banque correctement il faut d'abord lancer le serveur puis lancer **trois** fois le client. Il faut lancer trois fois car nous avons trois agences.
