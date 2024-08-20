'''
service 1 00001800-0000-1000-8000-00805f9b34fb Generic Access Profile
  characteristic 2 00002a00-0000-1000-8000-00805f9b34fb Device Name ['read']
  characteristic 4 00002a01-0000-1000-8000-00805f9b34fb Appearance ['read']
  characteristic 6 00002a02-0000-1000-8000-00805f9b34fb Peripheral Privacy Flag ['read', 'write']
  characteristic 8 00002a03-0000-1000-8000-00805f9b34fb Reconnection Address ['write']
  characteristic 10 00002a04-0000-1000-8000-00805f9b34fb Peripheral Preferred Connection Parameters ['read']

service 12 00001801-0000-1000-8000-00805f9b34fb Generic Attribute Profile
  characteristic 13 00002a05-0000-1000-8000-00805f9b34fb Service Changed ['indicate']
    descriptor 00002902-0000-1000-8000-00805f9b34fb (Handle: 15): Client Characteristic Configuration

service 16 0000ffe0-0000-1000-8000-00805f9b34fb Vendor specific
  characteristic 17 0000ffe1-0000-1000-8000-00805f9b34fb www.jnhuamao.cn ['read', 'write-without-response', 'write', 'notify']
    descriptor 00002902-0000-1000-8000-00805f9b34fb (Handle: 19): Client Characteristic Configuration
    descriptor 00002901-0000-1000-8000-00805f9b34fb (Handle: 20): Characteristic User Description
'''

import asyncio
from bleak import BleakClient

address = "90:e2:02:b7:77:2b"
characteristic_uuid = "0000ffe1-0000-1000-8000-00805f9b34fb" 

async def notification_handler(sender, data):
    # Função chamada ao receber uma notificação
    print(f"{data.decode()}")

async def send_data(address, characteristic_uuid):
    async with BleakClient(address) as client:
        print(f"Connected: {client.is_connected}")

        # Inscreva-se para receber notificações
        await client.start_notify(characteristic_uuid, notification_handler)

        data = 'Hello from Python'

        while True:
            # Envia dados para o Arduino
            await client.write_gatt_char(characteristic_uuid, data.encode(), response=True)
            await asyncio.sleep(3)

# Executa a função send_data
asyncio.run(send_data(address, characteristic_uuid))
