#include <string>
#include <GL/glew.h>
#include "gameObject.h"
#include "labhelper.h"

class HeightFieldComp : public Component {
	
	int tesselation = 1024;
	int terrainScaling = 250.0f;

	GLuint heightfieldProgram = labhelper::loadShaderProgram("../project/heightfield.vert",
		"../project/shading.frag");
	
public:
	int m_meshResolution; // triangles edges per quad side
	GLuint m_texid_hf;
	GLuint m_texid_diffuse;
	GLuint m_vao;
	GLuint m_positionBuffer;
	GLuint m_uvBuffer;
	GLuint m_indexBuffer;
	GLuint m_numIndices;
	std::string m_heightFieldPath;
	std::string m_diffuseTexturePath;

	HeightFieldComp(const std::string& _heightfieldPath, const std::string& _terrainPhotoPath, GameObject* _go);

	// load height field
	void loadHeightField(const std::string &_heightFieldPath);

	// load diffuse map
	void loadDiffuseTexture(const std::string &_diffusePath);
	void createVBOs(int _tesselation);

	// generate mesh
	void generateMesh(int _tesselation);

	// render height map
	void update(float _dt) override;

};
