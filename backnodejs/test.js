// Simulation d'une montre Coap

const coap = require('coap');

console.log("request coap connect ...");
const req1 = coap.request('coap://localhost/connect/2025');
console.log("request coap connect OK");
req1.end();

console.log("request coap publish ...");
const req2 = coap.request('coap://localhost/2025/normal');
console.log("request coap publish OK");
req2.end();


