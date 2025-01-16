import asyncio
from aiocoap import Context, Message, resource  # Import resource explicitement

class SimpleResource(resource.Resource):  # Utilisation correcte de resource.Resource
    async def render_get(self, request):
        return Message(payload=b"Hello from CoAP server!")

async def main():
    # Création de la racine du serveur CoAP
    root = resource.Site()
    root.add_resource(['.well-known', 'core'], resource.WKCResource(root.get_resources_as_linkheader))
    root.add_resource(['example'], SimpleResource())

    # Création du contexte serveur CoAP
    await Context.create_server_context(root)

    # Garde le serveur en marche indéfiniment
    await asyncio.get_running_loop().create_future()

print("########################### PROGRAM RUNNING ###########################")
asyncio.run(main())

