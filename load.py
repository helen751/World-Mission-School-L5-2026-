import serial
import requests

# Change COM port (check Arduino IDE)
ser = serial.Serial('COM3', 9600)

while True:
    data = ser.readline().decode().strip()
    print(data)

    if "T:" in data:
        parts = data.split(',')

        temp = parts[0].split(':')[1]
        hum = parts[1].split(':')[1]

        url = f"http://localhost/insert.php?temperature={temp}&humidity={hum}"

        try:
            requests.get(url)
            print("Sent to server")
        except:
            print("Error sending")