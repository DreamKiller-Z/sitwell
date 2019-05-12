import board
import neopixel
number = 4
pixels = neopixel.NeoPixel(board.D18, number)

while(True):

	pixels[0] = (255, 0, 0)
	pixels[2] = (0,255,0)
print("blink")