#ifndef INIT_TABLE_H
#define INIT_TABLE_H

#include <list>
#include <vector>
#include <unordered_map>
#include <string>

#include "tinyXML\tinystr.h"
#include "tinyXML\tinyxml.h"

#include "core\assets.h"
#include "core\component.h"
#include "rendering\camera.h"
#include "core\transform.h"
#include "rendering\modelRenderer.h"
#include "rendering\particleRenderer.h"
#include "rendering\primitiveShapes.h"
#include "rendering\light.h"
#include "physics\physicsBody.h"
#include "physics\collider.h"
#include "physics\terrainCollider.h"
#include "rendering\robotRenderer.h"
#include "behaviour\custom.h"
#include "rendering\animator.h"
#include "rendering\GUI.h"

/*! \brief Data object for attributes
*/
struct AttribData{};
struct AttribDatai:AttribData { int data; }; //!< Int attrib data
struct AttribDataf:AttribData { float data; }; //!< Float attrib data
struct AttribDatas:AttribData { std::string data; }; //!< String attrib data

typedef std::shared_ptr<AttribData> SPtr_AttribData;





/*! \brief Data object for components
*/
class CompData
{
public:
	CompData(SPtr_Component comp);
	~CompData();
	
	void setAttribsToComponents(); //!< Set all of the attibs to whatever values the actual component currently has
	void setAttribsFromXML(TiXmlElement* compElmnt); //!< Set all of the attibs based on a tiny xml element
	void initializeComponent(); //!< Initialize component's values to values stored in comp data

	int attribCount(); //!< Total Number of attributes
	SPtr_Component getComp(); //!< Get pointer to actual component object

	int* attribPtrInt(int index);
	float* attribPtrFloat(int index);
	std::string* attribPtrString(int index);

	// Get Attribs
	int getIntAttrib(int index); //!< Get an int attribute by index
	float getFloatAttrib(int index); //!< Get a float attribute by index
	std::string getStringAttrib(int index); //!< Get a string attribute by index

private:
	SPtr_Component _comp; //!< Pointer to the actual component object
	std::vector<SPtr_AttribData> _attribs; //!< Attributes used as args in initialization. Bools and enums etc are stored as ints

	// Add attributes
	void addAttribi(int data); //!< Add an int attribute
	void addAttribf(float data); //!< Add a float attribute
	void addAttribs(std::string data); //!< Add a string attribute

	

	// Set Attribs
	void setIntAttrib(int index, int value); //!< Set an int attribute by index
	void setFloatAttrib(int index, float value); //!< Set a float attribute by index
	void setStringAttrib(int index, std::string value); //!< Set a string attribute by index

	// Helper functions for getting tinyxml data more easily
	int to_int(TiXmlElement* elmnt, std::string attribute);
	float to_float(TiXmlElement* elmnt, std::string attribute);

};






/*! \brief Data object for game objects
*/
struct GOData
{
	//std::string name;
	std::list<CompData> components;
};







/*! \brief Info on how to initialize a scene

	The init table is a representation of a scene XML file in local memory.
	It can be used to create and initalize a new scene or it can be used to
	reset a scene back to its initial state without having to reload from XML.
	The latter use is especially needed for editor mode, when constant testing
	from the init state is needed. The init table is implemented as a vector of
	Game Object datas, each with a list of components and behavaiours and their innit
	values (used a typedef to make it easy to change to full class if more functiaonality needed)

*/
typedef std::unordered_map<unsigned int, GOData> InitTable;
typedef std::unordered_map<unsigned int, GOData>::iterator InitTableIterator;


#endif