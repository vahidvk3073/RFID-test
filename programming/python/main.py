import serial
import time
import struct
from datetime import datetime

file_path = 'C:\ARM\Star5Lock\RFIDtest\output.txt'

tag_numbers = [
    "4327D7B663",
    "43AB18C683",
    "4341F63617",
    "4345F68C27",
    "43E0054DC6",
    "4394CE667D"
]

# function for send motor number,angle and speed


def servo_motor_control(motor_1_angle, motor_1_speed, motor_2_angle, motor_2_speed):
    START_BYTE = 0xFF
    STOP_BYTE = 0x0A

    received_data = 0

    m_packet = struct.pack('<BBBBBB', START_BYTE,
                           motor_1_angle, motor_1_speed, motor_2_angle, motor_2_speed, STOP_BYTE)

    servo_serial.write(m_packet)

    if servo_serial.in_waiting > 0:
        received_data = servo_serial.readline().decode()
        print(f"received message : {received_data}")

    return received_data


# main program
servo_serial = serial.Serial(
    port='COM3', baudrate=115200, timeout=1)

RFIDreader_serial = serial.Serial(
    port='COM8', baudrate=9600, timeout=1)

print('start after 5 second...')
for i in range(0, 5):
    print(f'{5 - i} \r\n')
    time.sleep(1)

print('start\r\n')

angle = 0
index = 0

while True:

    # send data to motors, 0 is fastest,100 is slowest
    received_data = servo_motor_control(motor_1_angle=angle, motor_1_speed=50,
                                        motor_2_angle=12, motor_2_speed=5)


    if RFIDreader_serial.in_waiting > 0:

        data = RFIDreader_serial.read(5)

        received_card = data.hex().upper()

        print(f'received_card : {received_card}\n')

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        if str(received_card) == tag_numbers[index]:
            result = "OK\n"
            print('OK')
        else:
            result = "WRONG\n"
            print('WRONG')

        with open(file_path, 'a') as file:
            file.write(
                f"{timestamp} | Received: {received_card} | List[{index}]:{tag_numbers[index]} | Result: {result}\n"
            )

    angle = angle + 6
    if (angle == 36):
        angle = 0

    index = index + 1
    if (index == 6):
        index = 0

    time.sleep(10)
