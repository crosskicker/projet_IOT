# Backend COAP

## Run project
Run server :  
``` python3 main.py ``` 

If you want to test without a client as an arduino you use the test client :  
Run the client test :  
```python3 ./test/client.py```

### pre-requisites :  
 - aiocoap

# Backend Node.js
> Laissez moi faire


# Front
Le front est dans le dossier [`UI-IoT`](/UI-Iot).

Dans [`src/App.vue`](/src/App.vue) il y a du code a décommenter dans la section `script setup` qui correspond au *JavaScript* de la page !!!

Il faut créer un serveur websocket pour avoir en temps réel les infos ...

## Project Setup
Se situer dans le dossier UI-IoT/

### Installer nodejs et npm
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
```sh
npm install
```

### Compile et run en temps réel le modèle

```sh
npm run dev
```

### Compile et creer les 3 fichiers `.html`, `.css`, `.js`

```sh
npm run build
```
