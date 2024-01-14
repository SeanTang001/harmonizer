import asyncio
import websockets
import mido
import fluidsynth

import websocket
import time

wss = websocket.WebSocket()

wss.connect("ws://localhost:9000")

fs0 = fluidsynth.Synth()
fs0.start(driver = 'pulseaudio')
# sfid0 = fs.sfload(r'/home/seantang001/Downloads/VintageDreamsWaves-v2.sf2')
sfid0 = fs0.sfload(r'/home/seantang001/Downloads/temp.sf2')
# program_select(track, soundfontid, banknum, presetnum)
fs0.program_select(0, 1, 0, 0)


fs1 = fluidsynth.Synth()
fs1.start(driver = 'pulseaudio')
sfid0 = fs1.sfload(r'/home/seantang001/Downloads/temp.sf2')
fs1.program_select(0, 1, 128, 0)

web_clients = []

counter = 0

async def server(ws:str, path:int):
    chan = 0
    if path[1:] == "drum":
        fs =fs1
    elif path[1:] == "piano":
        fs = fs0
    elif path[1:] == "web":
        fs = fs0
        web_clients.append(ws)
    else:
        fs = fs0
    print(path[1:])
    print(web_clients)
    try:
        while True:
            message = await ws.recv()
            for message in mido.parser.parse_all(message):
                if message.note < 60:
                    continue
                else:
                    if (message.type == "note_on"):
                        print(path[1:]+" hit")
                        fs.noteon(0, message.note, message.velocity)
                        wss.send(str(message.note).encode('ascii'))
                    else:
                        fs.noteoff(0, message.note)
    except Exception as e:
        print(e)

Server = websockets.serve(server, 'localhost', 5678, open_timeout=600000)

asyncio.get_event_loop().run_until_complete(Server)
asyncio.get_event_loop().run_forever()