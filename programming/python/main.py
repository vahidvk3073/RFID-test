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

previous_time = 0
current_time = 0

angle = 0
index = 0

# send motor number,angle and speed function
def ServoMotorControl(motor_number, motor_angle, motor_speed):
    START_BYTE = 0xFF
    STOP_BYTE = 0x0A

    received_data = 0

    print(f"Motor Angle: {motor_angle}")

    m_packet = struct.pack('<BBBBB', START_BYTE,
                           motor_number, motor_angle, motor_speed, STOP_BYTE)

    servo_serial.write(m_packet)

    # print(f"Packet: {m_packet}")

    while True:
        if servo_serial.in_waiting > 2:
            received_data = servo_serial.readline().decode().strip()
            print(f"received message : {received_data}")
            break

    return received_data


#check RFID Reader function
def RFIDReaderCheck(index):
    last_time = time.time()

    while True:
        #check if READER could not read TAG after 3 second
        current_time = time.time()
        
        if (current_time - last_time) > 5:
            return 0
        
        #check if READER could read TAG
        if RFIDreader_serial.in_waiting > 4:

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
                    f"{timestamp} | Received: {received_card} | List[{index}]: {tag_numbers[index]} | Result: {result}\n"
                )

            return 1

# main program
servo_serial = serial.Serial(
    port='COM8', baudrate=115200, timeout=1)

RFIDreader_serial = serial.Serial(
    port='COM11', baudrate=9600, timeout=1)

print('start after 5 second...')
for i in range(0, 5):
    print(f'{5 - i} \r\n')
    time.sleep(1)

print('start\r\n')



send_data_to_motor_1 = 1
send_data_to_motor_2 = 0

while True:
    # send data to motor 1 
    if send_data_to_motor_1 == 1:
        motor_1_received_data = ServoMotorControl(
            motor_number=1, motor_angle=angle, motor_speed=50)

        #check motor state
        status = motor_1_received_data.find("OK1")

        if  status == -1:
            print('motor 1 send command failed')

            send_data_to_motor_1 = 0
            send_data_to_motor_2 = 0
        else :
            send_data_to_motor_1 = 0
            send_data_to_motor_2 = 1
            
            print('motor 1 send command success')
            #angle for next reading
            angle = angle + 6
            if (angle == 36):
                angle = 0

    # send data to motor 2 -----> 0 ms is fastest,100 ms is slowest
    if send_data_to_motor_2 == 1:
        motor_2_received_data = ServoMotorControl(
            motor_number=2, motor_angle=13, motor_speed=100)

        status = motor_2_received_data.find("OK2")

        if  status == -1:
            print('motor 2 send command failed')
            
            #send motor 2 cammand again
            send_data_to_motor_1 = 0
            send_data_to_motor_2 = 1
        else :
            print('motor 2 send command success')
            
            is_read_card = RFIDReaderCheck(index)

            if is_read_card == 1:
                #go to setting next angle
                print('Well Done...!read TAG and data saved\n')
                send_data_to_motor_1 = 1
                send_data_to_motor_2 = 0

                index = index + 1
                if (index == 6):
                    index = 0
            else :
                #RFID Reader could not read TAG, send motor 2 cammand again
                print('TimeOUT!could not read TAG,try again\n')
                send_data_to_motor_1 = 0
                send_data_to_motor_2 = 1

    if (send_data_to_motor_1 == 0 and send_data_to_motor_2 == 0):
        print('oops...!stop process')
    
    time.sleep(7)
    
    RFIDreader_serial.reset_input_buffer()

 

        
