const express = require("express");
const servExpress = express();
const PORT=8000; // port serveur web
const servHttp = require("http").createServer(servExpress); // server http et pas express pour recup l'instance avec websocket
const { WebSocketServer } = require("ws");
const servWs = new WebSocketServer( { server : servHttp } ); //pour la table en temps reel
const servCoap = require('coap').createServer();

// Un seul user pour la demo
const userList = [ {
    nodeid: 2025,
    nom: "Martin",
    prenom: "Jean",
    chambre: 101,
    etat: "shutdown"
}];

// ====== COAP ======
servCoap.on('request', (req, res) => {
    console.log("CoAP request received");
    const url = req.url.split('/');

    // Lorsqu'une montre s'allume, elle doit envoyer son nodeID sur /connect
    if (url[1]==="connect") {

        if (url[2]==="2025") { // seul user pour la demo
            userList[0].etat = "connected";
            if (wsList.length!=0) {
                const jsonString = JSON.stringify(userList);
                wsList[0].send(jsonString);
                console.log("blob");
            }
        }
    }
    // une montre envoie les alertes sur /${nodeID}, ici /2025 pour la demo
    else if (url[1]==="2025"){
        // On va considérer 3 etats : normal - alerte cardiaque - alerte chute
        userList[0].etat = url[2];
        const jsonString = JSON.stringify(userList);
        wsList[0].send(jsonString);
        console.log("blob");
    }
  res.end();
});

// the default CoAP port is 5683
servCoap.listen(5683);

// ====== Express ======
servExpress.use(express.json());
servExpress.use(express.static("public", {extensions : ["html","htm"]} ));


// ====== WebSocket ======
// on considere une seule connection pour la demo
const wsList = [];
servWs.on("connection", (ws)=> {
    console.log("interface connecte");
    wsList.push(ws);
    ws.on('error', console.error);
    const jsonString = JSON.stringify(userList);
    ws.send(jsonString);
    console.log("blob");
})

// ====== http server ======
servHttp.listen(PORT, () =>  {
    console.log(`Serveur Web ecoute sur ${PORT}`);
})