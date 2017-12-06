import cv2
import time
import serial


def tirarFoto():
	camera = cv2.VideoCapture(0)
	ok, img = camera.read()
	
	if ok:
		x = time.localtime()
		arquivo = '%d-%02d-%02d-%02d-%02d-%02d.jpeg' % (x[0], x[1], x[2], x[3], x[4], x[5])
		cv2.imwrite(arquivo, img)
	
	camera.release()
	
	return ok


		
arduino = serial.Serial('COM3', 9600)

while True:
	sinal = arduino.read()
	if sinal == '1':
		for i in range(10):
			tirarFoto()
			time.sleep(1)


