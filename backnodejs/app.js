const express = require("express");
const http = require("http");
const servExpress = express();
const PORT=8000;
const servHttp = http.createServer(servExpress);
const wsCreateServer = require("ws").createServer
const servWs = wsCreateServer( { servHttp } ); //pour la table en temps reel

servExpress.use(servExpress.json());

const userList = []; // Liste user a changer avec coap
servExpress.get("/userlist", (_req,res) => {
    res.json(userList);
})

servWs.on("connection", (ws)=> {
    ws.on('error', console.error);

    ws.send();
})

servHttp.listen(PORT, () =>  {
    console.log(`Serveur Web ecoute sur ${PORT}`);
})