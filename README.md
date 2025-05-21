# 3IF_AirWatcher
TP de Génie Logiciel
Lien du document Word des rendus : 
https://insalyonfrance-my.sharepoint.com/:w:/g/personal/edosanjos_insa-lyon_fr/EVSNzSARSPZKgMgsQqCgS6YBehI4z2Srng06fMhz2f5D9A

## TO-DO LIST: RENDU APP V1
- Implémenter le service d'authentification ➕
- Implémenter la fonction Administrateur d'évaluation des différents algorithmes ➕
- Remettre en ordre les histoires de UserDataAccess -> PointsManager 😖
- analyzeCleaner() provoque une erreur de segmentation et son retour est vraiment pas pratique ✨
- analyzeSensor() semble trouver que chaque capteur est suspect 😧
- computeZone() attribue les points aux utilisateurs, mais il semble avoir un erreur 💸

- Supprimer les branches obsolètes ☠️
- Clean le code 🧹

## Ajustements au niveau du rendu PDF
- À terme, il faudra reprendre le diagramme de classes, car on a fait quelques changements
- Trouver un moyen d'agrandir le diagramme de classe, pour qu'il puisse être lu en version imprimée (au moins format paysage)
- La relation entre un capteur et une mesure est une composition, changer le style de la flèche

## Question
- On check les autorisations associées à la session dans l'interface ou dans les services ?
