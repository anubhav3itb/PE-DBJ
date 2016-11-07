import math
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
						
						if(co_in):
							index = index+1
							index = index+1
						
						elif(norm):
							index = index+1
							index = index+1
							index = index+1
					
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

