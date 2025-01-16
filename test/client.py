import logging
import asyncio
from aiocoap import *

logging.basicConfig(level=logging.INFO)


async def main():
    """Effectue une requête PUT vers le serveur CoAP sur localhost."""
    context = await Context.create_client_context()

    # Attente de 2 secondes avant l'envoi de la requête
    await asyncio.sleep(2)

    # Charge utile (contenu de l'alerte)
    payload = b"Alert: man is down.\n" * 30
    request = Message(code=PUT, payload=payload, uri="coap://localhost/urgence")

    # Envoyer la requête et attendre une réponse
    try:
        response = await context.request(request).response
        print(f"Result: {response.code}\n{response.payload.decode('utf-8')}")
    except Exception as e:
        print(f"Error while sending request: {e}")


if __name__ == "__main__":
    asyncio.run(main())
