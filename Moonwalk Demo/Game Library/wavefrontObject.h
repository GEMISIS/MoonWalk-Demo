#include <vector>
#include "drawableObject.h"

typedef enum
{
	NONE = 0,
	TRIANGLES = 3,
	QUADS = 4
}drawType_t;

struct vertex_t
{
	float x, y, z;
};

struct textureCoords_t
{
	float u, v;
};

struct face_t
{
	unsigned int modelVerticesHandle;
	unsigned int modelUVsHandle;
	unsigned int modelNormalsHandle;

	bool hasUVs;
	bool hasNormals;

	std::vector<unsigned int> faceVertexIndices;
	std::vector<unsigned int> faceUVIndices;
	std::vector<unsigned int> faceNormalIndices;

	std::vector<float> outputVertexIndices;
	std::vector<float> outputUVIndices;
	std::vector<float> outputNormalIndices;

	drawType_t drawType;
};

class wavefrontObject : drawableObject
{
public:
	void loadGraphics(const char* fileName);
	void draw();
protected:
	std::vector<char> fileName;
	std::vector<vertex_t> vertexIndices;
	std::vector<textureCoords_t> uvIndices;
	std::vector<vertex_t> normalIndices;

	std::vector<face_t> faces;
private:
};
