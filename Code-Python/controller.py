import sys
from view import *
from model import *

model = Model()
view = View()

class Controller:
	
	def __main__(self):
		self.flag = 1
		self.oldX = -13
		self.oldY = -13
		self.centx = 0.0
		self.centy = 0.0
		self.centz = 0.0
		self.state = {"UP":0,"DOWN":1}
		self.mState = 0		

	def keyboard(self, key, x, y):
		if (key == chr(27) or key == 'q'):
			print "Quiting ..."
			exit(-1)
		elif (key == 'l'):
			view.angle += 0.5
		elif (key == 'r'):
			view.angle -= 0.5
		elif (key == '+'):
			view.scale += 0.2
		elif (key == '-'):
			view.scale -= 0.2
		 
		glutPostRedisplay()
	
	def glutMotion(self, x, y):
		if (self.mState == self.state["DOWN"]):
			view.rotate(self.oldX, self.oldY, x, y)
			glutPostRedisplay()
		self.oldX = x
		self.oldY = y
		
	def glutMouse(self, button, states, x, y):
		
		dist = 0.0
		px = 0
		py = 0
		
		if(states == GLUT_DOWN):
			
			if button == GLUT_LEFT_BUTTON:
				self.mState = self.state['DOWN']
				self.oldX = x
				self.oldY = y
			if button == GLUT_RIGHT_BUTTON:
				self.oldX = x
				self.oldY = y
	
		elif (states == GLUT_UP):
			self.mState = self.state["UP"]
			if button == GLUT_LEFT_BUTTON:
				self.oldX = x
				self.oldY = y
		
		glutPostRedisplay()
		
		
	def SpecialKeys(self, key, x, y):
		if (key == GLUT_KEY_LEFT):
			view.transx+=0.1
		
		elif (key == GLUT_KEY_UP):
			view.transy-=0.1
		
		elif (key == GLUT_KEY_RIGHT):
			view.transx-=0.1
		
		elif (key == GLUT_KEY_DOWN):
			view.transy+=0.1
		
		glutPostRedisplay()
		
	def run(self, arguments):
		model.readObject(arguments[1])
		model.computeNormals()
		#model.mergePoints(0.0001)
		view.initRendering() #Initialize rendering
		#Set handler function for drawing
		glutDisplayFunc(view.draw)
		#Set handler function for window resize
		glutReshapeFunc(view.handleResize)
		#Set handler function for keypress
		glutKeyboardFunc(self.keyboard)
		#Set handler function for Special keypress
		glutSpecialFunc(self.SpecialKeys)
		glutMotionFunc(self.glutMotion)
		glutMouseFunc(self.glutMouse)
		glutMainLoop() #Start the main loop.
		
		
