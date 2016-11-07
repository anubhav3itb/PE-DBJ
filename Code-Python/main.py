import sys
from model import *
from view import *
from controller import *

model = Model()
view = View()

def main():

	arguments = sys.argv
	if (len(arguments) != 2):
		print "Usage: ./assign2 <ply filename>"
		exit(-1)		
	controller = Controller()
	glutInit(arguments)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA)
	glutInitWindowSize(400, 400) #Set the window size
	glutInitWindowPosition(50,50)
	#Create the window
	glutCreateWindow("Bezier and Legrange Curves")
	#~ glDepthMask(GL_TRUE)
	glDepthFunc(GL_ALWAYS)
	controller.run(arguments)

if __name__ == "__main__":
	main()		



