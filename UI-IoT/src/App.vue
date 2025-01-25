<script setup>
import { onBeforeUnmount } from 'vue'
import { ref } from 'vue'

const userList = ref([]);
// utiliser les websockets pour rester connecté au serveur pour les alertes sauf si tu proposes mieux
const socket = new WebSocket('ws://localhost:8000');

// Lorsque la connexion est ouverte
socket.onopen = () => {
  console.log('Connecté au serveur');
  // socket.send(JSON.stringify({ type: 'hello', message: 'Salut serveur!' }));
};

// Lorsque des données sont reçues
// event.data = userList
socket.onmessage = (event) => {
  console.log('Message reçu');
  console.log(event.data);
  if (event.data!=="ok")
    userList.value = [...JSON.parse(event.data)];
};

// En cas de fermeture
socket.onclose = () => {
  console.log('Connexion fermée par le serveur');
}


onBeforeUnmount(() => {
  socket.close();
})

/*
USER MODELE
{
  nodeid:0,
  nom:"Martin",
  prenom:"Jean",
  chambre:101,
  etat:"normal"-"alerte cardiaque"-"alerte chute"
}
*/

const pattern = ["NodeID","Nom","Pr&eacute;nom","Chambre", "Etat", "Etat Cardiaque", "Etat Chute", ""];

</script>

<template>
  <div id="core">
    <h1>Centre de contr&ocirc;le</h1>
    <table class="table">
      <thead>
        <tr>
          <th v-for="key in pattern" v-html=key></th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="(user, index) in userList" :class="[index ? 'impair' : 'pair', {alert : user.etat!=='connected'}]">
          <td v-for="value in Object.values(user)">{{ value }}</td>
          <td v-if="user.etat==='connected'"><ion-icon name="checkmark-circle-outline"></ion-icon></td>
          <td v-else><ion-icon name="alert-circle-outline"></ion-icon></td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<style scoped>
#core {
  display: flex;
  /* background-color: rgb(255, 204, 204); */
  flex-direction: column;
  width: 100%;
  height: auto;
  align-items: center;
  margin-top: 20px;
}

h1 {
  font-size: 46px;
}

table {
  border: 1px black solid;
  border-radius: 5px;
  border-spacing: 0px;
  width: 50%;
  min-width: 512px;
  max-width: 1024px;
  display: table;
}

thead {
  background-color: var(--color-background-mute);
  width: 100%;
}

th {
  padding: 0px;
  margin: 0px;
  font-size: large;
  text-align: left;
}

tr {
  padding: 0px;
  margin: 0px;
}

tr.pair {
  background-color : var(--color-background);
}

tr.impair {
  background-color : var(--color-background-soft);
}

.alert {
  background-color: rgb(255, 172, 172)!important;
}

ion-icon {
  position: relative;
  top : 2px;
  font-size: 16px;
}


</style>
