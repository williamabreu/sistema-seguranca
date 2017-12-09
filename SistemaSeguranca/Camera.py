# -*- coding: utf-8 -*-

import cv2
import time
import serial


nomePessoa = {
	"B0 A2 A9 89": "Visitante",
	"AA 23 92 3E": "Carla",
	"67 D5 02 6C": "Isadora",
	"97 23 02 6C": "Leticia"
}


def tirarFoto():
	camera = cv2.VideoCapture(0)
	ok, img = camera.read()
	
	x = time.localtime()
	arquivo = '%d-%02d-%02d-%02dh%02dm%02ds.jpeg' % (x[0], x[1], x[2], x[3], x[4], x[5])
	cv2.imwrite(arquivo, img)
	
	camera.release()

def salvarLogin(idCartao):
	arquivo = open('log.txt', 'a')
	x = time.localtime()
	horario  = '%02d/%02d/%d %02d:%02d:%02d' % (x[2], x[1], x[0], x[3], x[4], x[5])
	arquivo.write(horario + ' ' + nomePessoa[idCartao] + '\n')
	arquivo.close()
	
	

if __name__ == '__main__':
	
	# Serial.write(1) --> '\x01' --> tirar foto
	# Serial.write(2) --> '\x02' --> salvar login
	
	print 'Programa em execução!'
	
	arduino = serial.Serial('COM5', 9600)

	while True:
		sinal = arduino.read()
		if sinal == '\x01':
			tirarFoto()
		elif sinal == '\x02':
			idCartao = arduino.read_all()
			salvarLogin(idCartao)
			


