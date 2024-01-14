# Importing Libraries 
import serial 
import time 

arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1) 

def read(): 
    time.sleep(0.05) 
    data = arduino.readline() 
    return data 

if __name__ == "__main__":
    with open("serial.log", "w") as f:
        while True:
            data = read()
            f.write(data.decode('ascii'))
