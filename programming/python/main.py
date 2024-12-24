import serial
import time
import struct

file_path = 'C:\ARM\Star5Lock\RFIDtest\output.txt'

tag_numbers = [111, 222, 333, 444, 555, 666]

# function for send motor number,angle and speed


def servo_motor_control(motor_number, angle, speed):
    START_BYTE = 0xFF
    STOP_BYTE = 0x0A

    received_data = 0

    m_packet = struct.pack('<BBBBB', START_BYTE,
                           motor_number, angle, speed, STOP_BYTE)

    servo_serial.write(m_packet)

    while servo_serial.in_waiting() > 0:
        received_data = servo_serial.readline().decode()
        if (received_data != 0):
            print(f"received message : {received_data}")

    return received_data


# main program
servo_serial = serial.Serial(
    serial_port='COM3', baudrate=115200, timeout=1)

RFIDreader_serial = serial.Serial(
    serial_port='COM4', baudrate=115200, timeout=1)

while True:
    for i in range(0, 31, 6):

        # send data to motor 1
        received_data = servo_motor_control(motor_number=1, angle=i, speed=50)

        if "servo motor stopped success" in received_data:
            set_servo_angle = True

        while RFIDreader_serial.in_waiting >= 12:
            RFID_tag_number = RFIDreader_serial.read(12)

        if (RFID_tag_number == tag_numbers[i/6]):
            with open(file_path, 'a') as file:
                file.write("OK\n")
        else:
            with open(file_path, 'a') as file:
                file.write("WRONG\n")
                
        # send data to motor 2
        # servo_motor_control(motor_number=2, angle=i, speed=60)

        # if "data received succussfully" in received_data:
        #     print(f'succussfully sent to motor 2')
        #     print('============================================')

        time.sleep(5)
