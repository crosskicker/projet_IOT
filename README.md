# Backend COAP
## Tutoriel lancement
1. Se situer dans `backnodejs/`
2. lancer `nodejs app.js`
    - Avoir installé **nodejs** et les dépendances, [tutoriel](#installer-nodejs-et-npm)
3. Le serveur est lancé, accéder à l'interface sur `localhost:8000`, le serveur coap tourne au port par défaut : `5683`


## Installer nodejs et npm
[Installer Node.js](https://nodejs.org/fr/download)

#### Version Linux
```sh
# Télécharger et installer fnm :
curl -o- https://fnm.vercel.app/install | bash

# Télécharger et installer Node.js :
fnm install 22

# Vérifier la version de Node.js :
node -v # Doit afficher "v22.13.1".

# Vérifier la version de npm :
npm -v # Doit afficher "10.9.2".

```

#### Version Windows
```shell
# Télécharger et installer fnm :
winget install Schniz.fnm

# Télécharger et installer Node.js :
fnm install 22

# Vérifier la version de Node.js :
node -v # Doit afficher "v22.13.1".

# Vérifier la version de npm :
npm -v # Doit afficher "10.9.2".
```

### Instaler les packages necessaire
Se situer dans un dossier contenant `package.json` (**UI-IoT/** ou **backnodejs/**)
```sh
npm install
```

### Vue.js seulement
#### Compile et run en temps réel le modèle

```sh
npm run dev
```

#### Compile et creer les 3 fichiers `.html`, `.css`, `.js`

```sh
npm run build
```


## Python **Deprecated**
### Run project
Run server :  
``` python3 main.py ``` 

If you want to test without a client as an arduino you use the test client :  
Run the client test :  
```python3 ./test/client.py```

### pre-requisites :  
 - aiocoap

# Front
Le front est dans le dossier [`UI-IoT`](/UI-Iot).

## Project Setup
Se situer dans le dossier UI-IoT/
