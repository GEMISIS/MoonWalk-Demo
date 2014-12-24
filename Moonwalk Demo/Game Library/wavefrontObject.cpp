#include <Windows.h>
#include <gl\GL.h>
#include "extendedGL.h"
#include <algorithm>
#include "wavefrontObject.h"

void wavefrontObject::loadGraphics(const char* fileName)
{
	FILE* file = fopen(fileName, "rb");
	if(file == NULL) return;

	char lineHeader[256];
	int res = 0;

	bool creatingFaces = false;

	face_t tempFace;
	tempFace.hasUVs = false;
	tempFace.hasNormals = false;
	tempFace.drawType = NONE;
	fgets(lineHeader, 256, file);
	while(!feof(file))
	{
		if(lineHeader[0] == 'v' && lineHeader[1] == ' ')
		{
			vertex_t vertex;
			sscanf(lineHeader + 2, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			this->vertexIndices.push_back(vertex);
		}
		if(lineHeader[0] == 'v' && lineHeader[1] == 't' && lineHeader[2] == ' ')
		{
			textureCoords_t textureCoords;
			sscanf(lineHeader + 3, "%f %f\n", &textureCoords.u, &textureCoords.v);
			this->uvIndices.push_back(textureCoords);
		}
		if(lineHeader[0] == 'v' && lineHeader[1] == 'n' && lineHeader[2] == ' ')
		{
			vertex_t normals;
			sscanf(lineHeader + 3, "%f %f %f\n", &normals.x, &normals.y, &normals.z);
			this->normalIndices.push_back(normals);
		}
		if(lineHeader[0] == 'f' && lineHeader[1] == ' ')
		{
			creatingFaces = true;
			char vertices[4][256];
			int totalVertices = sscanf(lineHeader, "f %s %s %s %s\n", &vertices[0], &vertices[1], &vertices[2], &vertices[3]);
			if(tempFace.drawType == NONE)
			{
				if(totalVertices == 3)
				{
					tempFace.drawType = TRIANGLES;
				}
				else if(totalVertices == 4)
				{
					tempFace.drawType = QUADS;
				}
			}
			else
			{
				if(tempFace.drawType != totalVertices)
				{
					this->faces.push_back(tempFace);
					creatingFaces = false;
					tempFace.faceVertexIndices.clear();
					tempFace.faceUVIndices.clear();
					tempFace.faceNormalIndices.clear();
					tempFace.outputVertexIndices.clear();
					tempFace.outputUVIndices.clear();
					tempFace.outputNormalIndices.clear();
					tempFace.hasUVs = false;
					tempFace.hasNormals = false;
					tempFace.drawType = NONE;

					if(totalVertices == 3)
					{
						tempFace.drawType = TRIANGLES;
					}
					else if(totalVertices == 4)
					{
						tempFace.drawType = QUADS;
					}
				}
			}
			for(int i = 0;i < totalVertices;i += 1)
			{
				int type = 0;
				for(char* value = strtok(vertices[i], "/"); value != NULL; value = strtok(NULL, "/"))
				{
					switch(type)
					{
					case 0:
						tempFace.faceVertexIndices.push_back(atoi(value));
						break;
					case 1:
						tempFace.hasUVs = true;
						tempFace.faceUVIndices.push_back(atoi(value));
						break;
					case 2:
						tempFace.hasNormals = true;
						tempFace.faceNormalIndices.push_back(atoi(value));
						break;
					}
					type += 1;
				}
			}
		}
		else if(creatingFaces)
		{
			this->faces.push_back(tempFace);
			creatingFaces = false;
			tempFace.faceVertexIndices.clear();
			tempFace.faceUVIndices.clear();
			tempFace.faceNormalIndices.clear();
			tempFace.outputVertexIndices.clear();
			tempFace.outputUVIndices.clear();
			tempFace.outputNormalIndices.clear();
			tempFace.hasUVs = false;
			tempFace.hasNormals = false;
			tempFace.drawType = NONE;
		}
		fgets(lineHeader, 256, file);
	}
	if(creatingFaces)
	{
		this->faces.push_back(tempFace);
		creatingFaces = false;
		tempFace.faceVertexIndices.clear();
		tempFace.faceUVIndices.clear();
		tempFace.faceNormalIndices.clear();
		tempFace.outputVertexIndices.clear();
		tempFace.outputUVIndices.clear();
		tempFace.outputNormalIndices.clear();
		tempFace.hasUVs = false;
		tempFace.hasNormals = false;
		tempFace.drawType = NONE;
	}

	for(unsigned int j = 0;j < this->faces.size();j += 1)
	{
		for(unsigned int i = 0;i < this->faces[j].faceVertexIndices.size();i += 1)
		{
			unsigned int vertexIndex = this->faces[j].faceVertexIndices[i];
			this->faces[j].outputVertexIndices.push_back(this->vertexIndices[vertexIndex - 1].x);
			this->faces[j].outputVertexIndices.push_back(this->vertexIndices[vertexIndex - 1].y);
			this->faces[j].outputVertexIndices.push_back(this->vertexIndices[vertexIndex - 1].z);

			if(this->faces[j].hasUVs)
			{
				unsigned int uvIndex = this->faces[j].faceUVIndices[i];
				this->faces[j].outputUVIndices.push_back(this->uvIndices[uvIndex - 1].u);
				this->faces[j].outputUVIndices.push_back(this->uvIndices[uvIndex - 1].v);
			}
			if(this->faces[j].hasNormals)
			{
				unsigned int normalIndex = this->faces[j].faceNormalIndices[i];
				this->faces[j].outputNormalIndices.push_back(this->normalIndices[normalIndex - 1].x);
				this->faces[j].outputNormalIndices.push_back(this->normalIndices[normalIndex - 1].y);
				this->faces[j].outputNormalIndices.push_back(this->normalIndices[normalIndex - 1].z);
			}
		}
	}
	for(unsigned int j = 0;j < this->faces.size();j += 1)
	{
		glGenBuffers(1, &this->faces[j].modelVerticesHandle);
		glBindBuffer(GL_ARRAY_BUFFER, this->faces[j].modelVerticesHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->faces[j].outputVertexIndices.size(), 
			&this->faces[j].outputVertexIndices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if(this->faces[j].hasUVs)
		{
			glGenBuffers(1, &this->faces[j].modelUVsHandle);
			glBindBuffer(GL_ARRAY_BUFFER, this->faces[j].modelUVsHandle);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->faces[j].outputUVIndices.size(), 
				&this->faces[j].outputUVIndices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if(this->faces[j].hasNormals)
		{
			glGenBuffers(1, &this->faces[j].modelNormalsHandle);
			glBindBuffer(GL_ARRAY_BUFFER, this->faces[j].modelNormalsHandle);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->faces[j].outputNormalIndices.size(), 
				&this->faces[j].outputNormalIndices[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}

void wavefrontObject::draw()
{
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	for(unsigned int i = 0;i < this->faces.size();i += 1)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, this->faces[i].modelVerticesHandle);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		
		if(this->faces[i].hasNormals)
		{
			glEnableClientState(GL_NORMAL_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, this->faces[i].modelNormalsHandle);
			glNormalPointer(GL_FLOAT, 0, 0);
		}
		
		if(this->faces[i].hasUVs)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, this->faces[i].modelUVsHandle);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
		}

		switch(this->faces[i].drawType)
		{
		case NONE:
			glDrawArrays(GL_TRIANGLES, 0, this->faces[i].outputVertexIndices.size() / 3);
			break;
		case TRIANGLES:
			glDrawArrays(GL_TRIANGLES, 0, this->faces[i].outputVertexIndices.size() / 3);
			break;
		case QUADS:
			glDrawArrays(GL_QUADS, 0, this->faces[i].outputVertexIndices.size() / 4);
			break;
		}

		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
