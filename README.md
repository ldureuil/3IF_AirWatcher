# 3IF_AirWatcher
### Auteurs : B3227 - DOS ANJOS Enzo, RICO VILLA Xchel ; B3228 - DUREUIL Lilas, MADRANE Karim

## Description de l'application

AirWatcher est une application en mode console qui analyse les données de capteurs et produit des statistiques sur la qualité de l'air et son évolution. L'application est principalement utilisée par une agence gouvernementale, et intègre les questions de fiabilité, de performance, et de sécurité. Ses principales fonctionnalités sont :
- Calculer des statistiques personnalisées sur la qualité de l'air,
- Fournir des données à la fois sur les capteurs en service et sur les purificateurs d'air installés,
- Gérer les points des particuliers possédant des capteurs,
- Exclure les capteurs de particuliers jugés suspects,
- Mesurer les performances de l'application.

## Consignes pour la compilation et l'exécution

Pour compiler l'application, placez-vous dans le dossier src (cd src), puis exécutez la commande "make".
Lancez ensuite l'application avec "./AirWatcher".

Pour compiler les mains des tests unitaires et fonctionnels, utilisez la commande "make test".
Pour les tests unitaires, exécutez la commande "./Unit_Test_AirWatcher" ;
lancez les tests fonctionnels grâce à "./Functional_Test_AirWatcher".

Pour le nettoyage, utilisez "make cleano" (conserve les exécutables) et "make clean" (supprime tous les fichiers compilés)

## Consignes pour l'authentification

Pour pouvoir tester l'application en empruntant les différents rôles utilisateurs, voici les combinaisons login / mot de passe à emprunter :
- Rôle Administrateur : admin / mdp
- Rôle Fournisseur : fournisseur / mdp
- Rôle Particulier : particulier0 / mdp ou particulier1 / mdp
- Rôle Utilisateur : user / mdp