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
* "repertoire.h"
* "client.h"
* "serveur.h"
* "operator.h"



# Références
* {}

# Difficulté
* Remi : 4/10
* Vincent : ?/10

# Commentaires
* Les trois premiers exercices sur les répertoires sont executables depuis le fichier main.c une fois compilé.

### Synopsis de main :
```c
./main NUM CHEMIN
```
où `NUM` est 1, 2 ou 3 selon le numéro de l'exercice et `CHEMIN` est un chemin vers un dossier.

* Les trois derniers exercices se font par les fichiers client.c et serveur.c. Tapez :
```c
help
```
ou
```c
man calcule
```
dans la console cliente pour avoir de l'aide.

```c
envoie [MESSAGE]
```
est la commande correspondant à l'exercice 4.

```c
calcule [:] OPERATEUR NUM1 [NUM2]
```
est la commande correspondant à l'exercice 5.

```c
calcule [:] moyenne DOSSIER_DE_NOTES
```
est la commande correspondant à l'exercice 5.
