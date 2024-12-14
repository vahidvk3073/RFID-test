import serial
import time
import struct

ALL_MOTOR_NUMBER = 2
motor_number = 0
serial_port = 'COM3'
baudrate = 115200

# define function for send motor number,angle and speed


def servo_motor_control(motor_number, angle, speed):
    START_BYTE = 0xFF
    STOP_BYTE = 0x0A

    received_data = 0

    m_packet = struct.pack('<BBBBB', START_BYTE,
                           motor_number, angle, speed, STOP_BYTE)

    ser.write(m_packet)

    received_data = ser.readline().decode()
    # if (received_data != 0):
    #     print(f"received message : {received_data}")

    return received_data


ser = serial.Serial(serial_port, baudrate, timeout=1)

while True:
    for i in range(6, 37, 6):
        # send data to motor 1
        servo_motor_control(motor_number=1, angle=i, speed=20)

        # if "data received succussfully" in received_data:
        #     print('succussfully sent to motor 1')
        #     print('============================================')

        # send data to motor 2
        servo_motor_control(motor_number=2, angle=i, speed=60)

        # if "data received succussfully" in received_data:
        #     print(f'succussfully sent to motor 2')
        #     print('============================================')

        start_time = time.time()
        while (time.time() - start_time < 3):
            received_data = ser.readline().decode()
            print(received_data)

        time.sleep(4)
