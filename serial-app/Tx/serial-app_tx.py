import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
	port='/dev/ttyUSB0',
	baudrate=9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS
)

ser.close()
ser.open()
#ser.close()
ser.isOpen()

print ('Enter your commands below.\r\nInsert "exit" to leave the application.')
input_phrase=1
while 1 :
	# get keyboard input
	input_phrase = input("Insert a COMMAND - (ex: n_uav-command)")
	#input = raw_input(">> ")
        # Python 3 users
	if input_phrase=='exit':
		ser.close()
		exit()
	else:
		#input_phrase.encode('ascii')
		# send the character to the device
		# (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
		input_phrase += "\r\n"
		ser.write(input_phrase.encode())
		out = ''
		# let's wait one second before reading output (let's give device time to answer)
		time.sleep(1)
		while ser.inWaiting() > 0:
			out += ser.read(1)
			if out != '':
				print (">>" + out)





