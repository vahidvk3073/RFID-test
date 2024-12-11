import serial
import time 
import struct

ALL_MOTOR_NUMBER = 2
motor_number = 0

def servo_motor_control(motor_number, angle, speed):
    START_BYTE = 0xFF
    STOP_BYTE = 0x0A

    m_packet = struct.pack('<BBBBB', START_BYTE,
                           motor_number, angle, speed, STOP_BYTE)

    return m_packet

ser = serial.Serial('COM3', baudrate=115200, timeout=1)

while True:
    for i in range(0, 37, 6):
        while motor_number < ALL_MOTOR_NUMBER:
            send_data = servo_motor_control(motor_number = 1, angle = i, speed = 50)
            ser.write(send_data)

            received_data = ser.readline().decode()
            if(received_data):
                print(received_data)
                motor_number = motor_number + 1
                break

        time.sleep(3)


    