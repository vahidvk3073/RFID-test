import serial
import time 

ser = serial.Serial('COM3', baudrate=115200, timeout=1)

while True:
    for i in range(0, 37, 6):
        send_data = str(i) + '\n'
        ser.write(send_data.encode())

        received_data = ser.readline().decode()
        if(received_data):
            print(received_data)

        time.sleep(2)
