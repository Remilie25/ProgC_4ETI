# Bibliothèques
* <stdio.h>
* <sys/types.h>
* <dirent.h>
* <string.h>
* <stdlib.h>
* <errno.h>
* <unistd.h>
* <sys/socket.h>
* <sys/epoll.h>
* <netinet/in.h>
* <fcntl.h>
* <arpa/inet.h>
* <signal.h>
* <math.h>
* <stdint.h>
* "repertoire.h"
* "client.h"
* "serveur.h"
* "operator.h"
* "bmp.h"
* "couleur.h"
* "cJSON.h"



# Références
* https://github.com/DaveGamble/cJSON?tab=readme-ov-file

# Difficulté
* Remi : 3/10
* Vincent : ?/10

#Commentaire
* cJSON n'est pas fourni. Voir la référence pour les options d'obtention.
* Nous sommes partis des fichiers serveurs et clients du TP5 auquel nous avons simplement rajouter les nouvelles fonctions, entêtes, etc qu'apportent les versions clients et serveurs du TP6. Puis nous avons unifié les codes. Dans la continuité du TP5, l'exercice 2 est accessible par la commande suivante :

```c
analyse IMAGE [NBR_COULEUR]
```

* L'étiquette pour l'analyse d'images et "analyse" et non "couleurs".