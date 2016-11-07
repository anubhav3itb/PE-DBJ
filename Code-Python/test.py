import math
import sys
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *




class Point:
	
	def __init__(self, x, y, z, normx, normy, normz):
		self.x = x
		self.y = y
		self.z = z
		self.normx = normx
		self.normy = normy
		self.normz = normz
		
	def __init__(self, x_coor, y_coor, z_coor):
		self.x = x_coor
		self.y = y_coor
		self.z = z_coor
		self.normx = 0.0
		self.normy = 0.0
		self.normz = 0.0
	
	def getX(self):
		return self.x
	
	def setX(self, x_coor):
		self.x = x_coor
		
	def getY(self):
		return self.y
	
	def setY(self, y_coor):
		self.y = y_coor
		
	def getZ(self):
		return self.z
	
	def setZ(self, z_coor):
		self.z = z_coor
		
	def getNormX(self):
		return self.normx
	
	def getNormY(self):
		return self.normy
	
	def getNormZ(self):
		return self.normz
		
	def Print(self):
		print self.x, ' ', self.y, ' ', self.z 
	
	def setNormal(self, nx, ny, nz):
		self.normx = nx
		self.normy = ny
		self.normz = nz
	
	def addNormal(self, nx, ny, nz):
		self.normx += nx
		self.normy += ny
		self.normz += nz
		
	def normNormal(self):
		n = 0.0
		n = math.sqrt(self.normx*self.normx + self.normy*self.normy + self.normz*self.normz)
		self.normx /= n 
		self.normy /= n 
		self.normz /= n

class Polygon:
	
	def __init__(self):
		self.no = -1
		self.vertices = []
		self.normx = 0
		self.normy = 0
		self.normz = 0
	
	def addVertex(self, point):
		self.vertices.append(point)
		
	def getPointAt(self, i):
		if (self.no != -1 and self.no != i):
			return self.vertices[i]
		else:
			return None
	
	def printVertices(self):
		for i in range(0,len(self.vertices)):
			self.vertices[i].Print()
	
	def drawPolygon(self):
		glBegin(GL_TRIANGLES)
		glColor4f(1., 1., 1., 1.)
		
		for i in range(0, len(self.vertices)):
			glNormal3f(self.vertices[i].getNormX(), self.vertices[i].getNormY(), self.vertices[i].getNormZ())
			glVertex3f(self.vertices[i].getX(), self.vertices[i].getY(), self.vertices[i].getZ())	
		glEnd()
		
	def computeNormal(self):
		n = 0.0
		
		v1x = 0.0
		v1y = 0.0
		v1z = 0.0
		
		v2x = 0.0
		v2y = 0.0
		v2z = 0.0
		
		v1x = self.vertices[1].getX() - self.vertices[0].getX()
		v1y = self.vertices[1].getY() - self.vertices[0].getY()
		v1z = self.vertices[1].getZ() - self.vertices[0].getZ()
	
		v2x = self.vertices[2].getX() - self.vertices[0].getX()
		v2y = self.vertices[2].getY() - self.vertices[0].getY()
		v2z = self.vertices[2].getZ() - self.vertices[0].getZ()
		
		normx = v1y*v2z - v1z*v2y
		normy = v1z*v2x - v1x*v2z
		normz = v1x*v2y - v1y*v2x
		n = math.sqrt(normx*normx + normy*normy + normz*normz)
		normx /= n 
		normy /= n
		normz /= n
		
		for i in range(0, len(self.vertices)):
			self.vertices[i].addNormal(normx, normy, normz)
		

class NewPolygon:
	
	def __init__(self):
		self.vertexes = []
		self.no = -1
		self.normx = 0
		self.normy = 0
		self.normz = 0
	
	def addVer(self, val):	
		self.vertexes.append(val)
	
	def getIdx(self, index):
		self.vertexes[idx]
		

class Model:
	
	def __init__(self):
		self.minx = 9999.0
		self.miny = 9999.0
		self.minz = 9999.0
		self.maxx = -9999.0
		self.maxy = -9999.0
		self.maxz = -9999.0
		self.tolerance = 0.0001
		self.points = []
		self.polygons = []
		self.polygos = []
		
	def render(self):
		drawAxis()
		drawObject()
		glPointSize(5)
		glBegin(GL_POINTS)
		glColor3f (1, 0, 0)
		glVertex3f(0, 0, 0)
		glEnd()
		
	def drawAxis(self):
		glBegin(GL_LINES)
		axis = 2.0
		
		#drawing x -axis
		glColor3f(0, 0, 1)
		glVertex3f( axis, 0, 0)
		glVertex3f(-axis, 0, 0)
	
		#drawing y -axis
		glColor3f(0, 1, 0)
		glVertex3f(0, axis, 0)
		glVertex3f(0, -axis,0)
	
		#drawing z -axis
		glColor3f(1, 0, 0)
		glVertex3f(0, 0, axis)
		glVertex3f(0, 0, -axis)
		glEnd()
	
	def drawObject(self):
		print "Model:", len(self.polygons)
		for i in range(0, len(self.polygons)):
			self.polygons[i].drawPolygon()
			
	def readObject(self, filename):
		print "File name is ",filename
		fp = open(filename, 'r')
		lines = fp.readlines()
		
		x = 0.0
		y = 0.0
		z = 0.0
		nx = 0.0
		ny = 0.0
		nz = 0.0
		
		num_vertex = 0
		num_faces = 0
		co_in = 0
		norm = 0
		
		sides = 0
		
		index = 0
		while(index < len(lines)):
			line = lines[index].split()
			
			for value in line:
				if value == "vertex":
					num_vertex = int(line[-1])
					print "number of vertices ",num_vertex	
					
				elif value == "face":
					num_faces = int(line[-1])
					print "number of faces ",num_faces
					
				elif (value == "confidence" or value == "intensity"):
					co_in = 1
				
				elif (value == "nx"):
					norm = 1
				
				elif (value == "end_header"):
					
					for i in range(index+1, num_vertex+index+1):
						line = lines[i].split()
						x = float(line[0])
						y = float(line[1])
						z = float(line[2])
						
						point = Point(x, y, z)
						self.points.append(point)
						
						if (self.minx > x):
							self.minx = x
						if (self.miny > y):
							self.miny = y
						if (self.minz > z):
							self.minz = z
						if (self.maxx < x):
							self.maxx = x
						if (self.maxy < y):
							self.maxy = y
						if (self.maxz < z):
							self.maxz = z
						
						#if(co_in):
						#	index = index+1
						#	index = index+1
						
						#elif(norm):
						#	index = index+1
						#	index = index+1
						#	index = index+1
					
					avgx = (self.maxx+self.minx)/2.0
					avgy = (self.maxy+self.miny)/2.0
					avgz = (self.maxz+self.minz)/2.0
					maxval = -9999
					
					if (abs(self.maxx - self.minx) > abs(self.maxy - self.miny) and abs(self.maxx - self.minx) > abs(self.maxz - self.minz)):
						maxval = self.maxx - self.minx
					elif (abs(self.maxy - self.miny) > abs(self.maxz - self.minz)):
						maxval = self.maxy - self.miny
					else:
						maxval = self.maxz - self.minz
					
					for k in range(0, num_vertex):
						self.points[k].setX((self.points[k].getX() - avgx)/maxval)
						self.points[k].setY((self.points[k].getY() - avgy)/maxval)
						self.points[k].setZ((self.points[k].getZ() - avgz)/maxval)
					
					self.minx = (self.minx - avgx)/maxval
					self.miny = (self.miny - avgy)/maxval
					self.minz = (self.minz - avgz)/maxval
			
					self.maxx = (self.maxx - avgx)/maxval
					self.maxy = (self.maxy - avgy)/maxval
					self.maxz = (self.maxz - avgz)/maxval
					
					print self.minx, " ", self.maxx
					print self.miny, " ", self.maxy
					print self.minz, " ", self.maxy
					print "maxval: ", maxval
					
					for i in range(index+1+num_vertex, num_faces+index+1+num_vertex):
						polygon = Polygon()
						poly = NewPolygon()
						#print line
						line = lines[i].split()
						
						sides = int(line[0])
						
						for j in range(sides):
							vertex_idx = int(line[j+1])
							polygon.addVertex(self.points[vertex_idx])
							poly.addVer(vertex_idx)
						
						self.polygons.append(polygon)
						self.polygos.append(poly)
						
					print "Size of points is ", len(self.points)
					print "Size of polygons is ", len(self.polygons)
							
			index = index+1
				

	def getDistance(self, p1, p2):
		distance = 0.0
		distance = math.sqrt(math.pow(p1.getX - p2.geX, 2.0) + math.pow(p1.getY - p2.getY, 2.0) + math.pow(p1.getZ - p2.geZ, 2.0))		
		
		if(distance < self.tolerance):
			return True
		else:
			return False
	
	def computeNormals(self):
		i = 0
		for i in range(len(self.polygons)):
			self.polygons[i].computeNormal()
			
		i = 0
		for i in range(len(self.points)):
			self.points[i].normNormal()
			
	def drawBoundingBox(self):
		glBegin(GL_LINES)
		glColor4f(0.4, 0.1, 0.25, 0)
		glVertex3f(self.minx, self.miny, self.minz)
		glVertex3f(self.maxx, self.miny, self.minz)
	
		glVertex3f(self.maxx, self.miny, self.minz)
		glVertex3f(self.maxx, self.maxy, self.minz)
	
		glVertex3f(self.maxx, self.maxy, self.minz)
		glVertex3f(self.minx, self.maxy, self.minz)
	
		glVertex3f(self.minx, self.maxy, self.minz)
		glVertex3f(self.minx, self.miny, self.minz)
	
		glEnd()
	
		glBegin(GL_LINES)
		glColor4f(1, 0, 0.2, 0)
		glVertex3f(self.minx, self.miny, self.maxz)
		glVertex3f(self.maxx, self.miny, self.maxz)
	
		glVertex3f(self.maxx, self.miny, self.maxz)
		glVertex3f(self.maxx, self.maxy, self.maxz)
	
		glVertex3f(self.maxx, self.maxy, self.maxz)
		glVertex3f(self.minx, self.maxy, self.maxz)
	
		glVertex3f(self.minx, self.maxy, self.maxz)
		glVertex3f(self.minx, self.miny, self.maxz)
		glEnd()
	
		glBegin(GL_LINES)
		glColor4f(1, 1, 0, 0)
		glVertex3f(self.minx, self.miny, self.minz)
		glVertex3f(self.minx, self.miny, self.maxz)
	
		glVertex3f(self.maxx, self.miny, self.minz)
		glVertex3f(self.maxx, self.miny, self.maxz)
		glEnd()
	
		glBegin(GL_LINES)
		glColor4f(1, 1, 0, 0)
		glVertex3f(self.minx, self.maxy, self.minz)
		glVertex3f(self.minx, self.maxy, self.maxz)
	
		glVertex3f(self.maxx, self.maxy, self.minz)
		glVertex3f(self.maxx, self.maxy, self.maxz)
		glEnd()
		
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
			view.transx-=0.1
		
		elif (key == GLUT_KEY_UP):
			view.transy+=0.1
		
		elif (key == GLUT_KEY_RIGHT):
			view.transx+=0.1
		
		elif (key == GLUT_KEY_DOWN):
			view.transy-=0.1
		
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
		
		
