/* Algorithm followed:
// foreach triangle
// REAL32[3] – Normal vector
// REAL32[3] – Vertex 1
// REAL32[3] – Vertex 2
// REAL32[3] – Vertex 3
// UINT16 – Attribute byte count
// end
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include <inttypes.h>

using namespace std;

int main(){

	unsigned char buffer[30];
	FILE *ptr; 
// Reading ktoolcav.stl. Command line arguments could be added.
	ptr = fopen("ktoolcav.stl","rb");
	uint8_t header[80];
	uint32_t no_triangles;
	int i = 0;
   	fread(&header,sizeof(header),1,ptr);
	fread(&no_triangles, sizeof(no_triangles), 1, ptr);

	float normal[3];
	float vertex1[3];
	float vertex2[3];
	float vertex3[3];
	for (i = 0; i < 3; i++){
		normal[i] = 0;
		vertex1[i] = 0;
		vertex2[i] = 0;
		vertex3[i] = 0;	
	}
	
	uint16_t attr;
	fread(&normal,sizeof(normal),1,ptr);
	fread(&vertex1, sizeof(vertex1),1,ptr);
	fread(&vertex2, sizeof(vertex2),1,ptr);
	fread(&vertex3, sizeof(vertex3),1,ptr);
	fread(&attr,sizeof(attr),1,ptr);
	cout << normal[0] << " " << normal[1] <<  " " << normal[2] << endl;
	cout << vertex1[0] << " " << vertex1[1] <<  " " << vertex1[2] << endl;
	cout << vertex2[0] << " " << vertex2[1] <<  " " << vertex2[2] << endl;
	cout << vertex3[0] << " " << vertex3[1] <<  " " << vertex3[2] << endl;	
	fclose(ptr);
	return 0;
}
