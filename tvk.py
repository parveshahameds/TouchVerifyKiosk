import serial
import time
arduino = serial.Serial('COM5', 9600, timeout=1)
time.sleep(2)  # Allow time for connection

while True:
    input("Press Enter and place your finger on the scanner...")  # Simulates fingerprint authentication

    # Generate a random fingerprint ID (Example)
    fingerprint_id = "FP" + str(time.time()).split('.')[1]  
    voter_id = input("Enter Voter ID: ")

    data_to_send = fingerprint_id + "," + voter_id
    print("Sending to Arduino:", data_to_send)
    
    arduino.write((data_to_send + "\n").encode())  # Send to Arduino

    # Wait for confirmation from Arduino
    while True:
        response = arduino.readline().decode().strip()
        if response:
            print("Arduino:", response)
        if response == "VOTE_COMPLETED":
            print("Vote recorded. Ready for the next voter!\n")
            break  # Exit loop to reset for next vote
