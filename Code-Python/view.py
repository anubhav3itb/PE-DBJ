import math
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
from model import *

model = Model()

class View:
	
	def __init__(self):
		self.h = 0
		self.w = 0
		self.transx = 0
		self.transy = 0
		self.transz = 0
		
		self.scale = 1
		self.angle = 0.0
		
	
	def draw(self):
		glClearColor(1.0, 1.0, 1.0, 1.0)		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
		position = [ 2.0, 2.0, 2.0, 1.0 ]
		glMatrixMode( GL_MODELVIEW )
		glLoadIdentity()
		
		
		gluLookAt(.05, .1, 2, 0., 0., 0, 0, 1, 0)
		print "in View"
		glPointSize(4.0)
		glBegin(GL_POINTS)
		glColor3f(1,0,0)
		glVertex3f(0,0,0)			
		glEnd()
		#rotation_transform[4][4]
		model.drawAxis()
		#trackball.rotationMatrix( rotation_transform )
		glLightfv (GL_LIGHT0, GL_POSITION, position)
		glEnable (GL_LIGHTING)
	
		glPushMatrix()
		glScalef(self.scale, self.scale, self.scale)
		glTranslatef(self.transx, self.transy, self.transz)
		glRotatef(self.angle, 1, 0, 0)
		#glMultMatrixf( &rotation_transform[0][0] ) 
	
		model.drawObject()
	
		#~ model.drawBoundingBox()
		glPopMatrix()
		glDisable (GL_LIGHTING)
		glutSwapBuffers()
		
	
	def initRendering(self):
		glClearColor(0.0, 0.0, .0, 0.0)
		w = glutGet( GLUT_WINDOW_WIDTH )
		h = glutGet( GLUT_WINDOW_HEIGHT )
		glViewport(0, 0, w, h)
		glEnable(GL_BLEND)
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
		glShadeModel(GL_SMOOTH)
		glEnable(GL_COLOR_MATERIAL)
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE)
	
		mat_specular = [ 1.0, 1.0, 1.0, 1.0 ]
		mat_shininess = [ 50.0 ]
	
		light_ambient = [ 0.0, 0.0, 0.0, 1.0 ]
		light_diffuse = [ 1.0, 1.0, 1.0, 1.0 ]
		light_specular = [ 1.0, 1.0, 1.0, 1.0 ]
		light_position = [ 2.0, 2.0, 2.0, 1.0 ]

		spot_direction = [ 0.0, 0.0, 0.0 ]
		lmodel_ambient = [ 0.2, 0.2, 0.2, 1.0 ]
		#~ glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient)
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE)
		#~ glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular)
		#~ glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess)
	
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse)
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular)
		glLightfv(GL_LIGHT0, GL_POSITION, light_position)
	
		#~ glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction)
		#~ glEnable(GL_LIGHTING)
		glEnable(GL_LIGHT0)
		glEnable(GL_DEPTH_TEST)
		glMatrixMode( GL_PROJECTION )
		glLoadIdentity()    
		gluPerspective( 60.0, w / h, 0., 10.0 )
		glMatrixMode(GL_MODELVIEW)
		glLoadIdentity()
		
	
	def handleResize(self, wt, ht):
		if (ht  == 0):
			ht = 1
		#Tell OpenGL how to convert from coordinates to pixel values
		w = wt
		h = ht
		glViewport(0,0, wt, ht)
		glMatrixMode(GL_PROJECTION) #Switch to setting the camera perspective
		#Set the camera perspective
		glLoadIdentity() #Reset the camera
		gluPerspective( 60.0, w / h, 0., 10.0 )
		glMatrixMode(GL_MODELVIEW)
		glLoadIdentity()
	

		
		
	
		
	
	
