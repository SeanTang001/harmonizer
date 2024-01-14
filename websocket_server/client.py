import mido
import random

def generate_random_midi_message():
    note = random.randint(60,72) # Random MIDI note between 60 and 72
    velocity = 127  # Random velocity between 40 and 80
    channel = 0
    return mido.Message('note_on', note=note, velocity=velocity, channel=channel).bin()

import websocket
import time
ws = websocket.WebSocket()
# ws.connect("ws://localhost:9000")
ws.connect("ws://4.tcp.us-cal-1.ngrok.io:17664/piano")

while True:
    print(type(generate_random_midi_message()))
    ws.send(generate_random_midi_message(), websocket.ABNF.OPCODE_BINARY)
    # ws.send(b'60')
    time.sleep(1)