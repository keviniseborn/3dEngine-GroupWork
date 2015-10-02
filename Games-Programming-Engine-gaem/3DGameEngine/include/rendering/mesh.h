#ifndef MESH_H
#define MESH_H

#include <vector>
#include <map>

#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "core\asset.h"

//! The constant values in this namespace match the location of attibs in both shaders and the VBO array in the mesh class
//  I've used consts instead of an enum as they will be refered to by number in the shaders (so easier to check correct number as written explicitly).
namespace MeshAttribs
{
	const unsigned int VERT = 0;
	const unsigned int INDEX = 1;
	const unsigned int NORMAL = 2;
	const unsigned int UV = 3;
	const unsigned int COLOUR = 4;
	const unsigned int BONE_IDS = 5;
	const unsigned int BONE_WEIGHTS = 6;
	const unsigned int TANGENT = 8;
	const unsigned int BITANGENT =9;

	const unsigned int NUM_ATTRIBS = 10; // Number may change with time if I add more attribs, but never used in shader so doesn't matter
}

struct VertexBoneData
{
	GLint ids[4];		/************** HARD CODED - Number of bones that can affect a vertex ******************/
	GLfloat weights[4];

};

//! \brief Mesh

class Mesh : public Asset
{
public:
	Mesh();
	~Mesh();

	void generateBuffers(); //!< Create VAO and buffer for data

	void setVerts(std::vector<glm::vec3> &verts); //!< Fill position data via vector
	void setIndices(std::vector<unsigned int> &indices); //!< Fill index data via vector
	void setNormals(std::vector<glm::vec3> &normals); //!< Fill normal data via vector
	void setUvs(std::vector<glm::vec2> &uvs); //!< Fill uv coordinate data via vector
	void setColours(std::vector<glm::vec3> &colours); //!< Fill colour data via vector
	void setBones(std::vector<glm::ivec4> &boneIds, std::vector<glm::vec4> &boneWeights); //!< Fill bone data via vector

	
	void setBoneOffset(std::vector<aiMatrix4x4> offSet); //!< Sets the offset of the bones (animation)
	void setNumJoints(int j);//!< Sets the number of joints in the mesh (animation)
	void setInverseTransform(aiMatrix4x4 inv); //!< Sets inverse transform as aiMatrix4x4 (animation)
	void setBoneMap(std::map<std::string, int> m); //!< Fill meshes bone map (animation)

	std::map<std::string, int> getBoneMap() { return boneMap; } //!< returns the meshes bonemap (animation)
	std::vector<aiMatrix4x4> getBoneOffset() {return m_BoneOffset; } //!< returns the meshes bone offset as a aiMatrix4x4 (animation)
	glm::mat4 getInverseTransform() {return m_GlobalInverseTransform; } //!< returns the global inverse as a mat4 (animation)
	int getNumJoints() {return numJoints;} //!< returns the number of joints in the mesh


	void setTangents(std::vector<glm::vec3> &tangents);
	void setBiTangents(std::vector<glm::vec3> &biTangents);

	GLuint getVao()  { return _vao; }
	int numIndices() { return _dataSize[MeshAttribs::INDEX]; }

	void setPrimID(int id) { _primID = id; }
	bool getPrimID() { return _primID; }

private:
	GLuint _vao; //!< The vao holding everything together!
	GLuint _buffers[MeshAttribs::NUM_ATTRIBS]; //!< To store handles for vbos / element buffer
	int _dataSize[MeshAttribs::NUM_ATTRIBS]; //!< Holds the number of elements in each buffer (useful for if you want to read from buffers later and also for drawing as we need to know how many elements)
	int _primID; //!< If prim shape, the ID of the primitive. If not, returns -1 (so can be used to determine if primitive)
	std::vector<aiMatrix4x4> m_BoneOffset; //!< vector of bone offsets for vertex position
	std::vector<aiMatrix4x4> m_BoneFinalTransform; //!< vector of final transforms 
	std::map<std::string, int> boneMap;	//!< map of bones to their ids
	glm::mat4 m_GlobalInverseTransform; //!< global inverse transform matrix
	int numJoints; //!< number of joints in mesh
};

#endif