import asyncio
from aiocoap import Context, Message, resource, CHANGED  # Import explicite de CHANGED


class Urgence(resource.Resource):
    def __init__(self):
        super().__init__()
        self.set_content(
            b"Alert received. Medical team on the way.\n"
        )

    def set_content(self, content):
        # Remplir la ressource avec une longueur maximale de 1024 octets
        self.content = content
        if len(self.content) < 1024:
            padding = content * ((1024 - len(self.content)) // 11)
            self.content += padding[: 1024 - len(self.content)]  # Ajuste exactement à 1024 octets

    async def render_put(self, request):
        # Afficher la charge utile reçue pour le débogage
        print(f"PUT payload received: {request.payload.decode('utf-8')}")

        # Répondre avec le code CHANGED (2.04)
        return Message(code=CHANGED, payload=self.content)


async def main():
    # Création de la racine du serveur CoAP
    root = resource.Site()
    root.add_resource(['.well-known', 'core'], resource.WKCResource(root.get_resources_as_linkheader))

    # Création de la ressource urgence
    root.add_resource(['urgence'], Urgence())

    # Création du contexte serveur CoAP
    await Context.create_server_context(root)

    # Garde le serveur en marche indéfiniment
    print("CoAP server running. Waiting for requests...")
    await asyncio.get_running_loop().create_future()


if __name__ == "__main__":
    print("########################### PROGRAM RUNNING ###########################")
    asyncio.run(main())
