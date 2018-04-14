#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "DerpEngine.h"
#include <TinyXML/tinyxml.h>
#include <TinyXML/tinystr.h>

#include <typeinfo>
#include <typeinfo.h>

#include "Lander.hpp"
#include "GameObject.h"

#include <map>

#include "Rigidbody.h"
#include "SpriteRenderer.h"

typedef void set_component_from_xml(TiXmlElement*, GameObject*);
typedef std::map<std::string, set_component_from_xml*> component_map;

component_map derp;

void build_gameobject_xml(GameObject *gameobject) {
	//create the actual document object (not yet wrote it to disk)
	TiXmlDocument xml_document;
	//declaration for the top of the xml document
	TiXmlDeclaration *declaration = new TiXmlDeclaration("1.0", "", "");
	xml_document.LinkEndChild(declaration);
	//create the gameobject elemetn and cretae a name attribute called name and get its value from gameobject
	TiXmlElement *gameobject_element = new TiXmlElement("Gameobject");
	gameobject_element->SetAttribute("name", gameobject->name.c_str());

	//create transform element, position element and give x and y to position
	TiXmlElement *transform_element = new TiXmlElement("Transform");
	TiXmlElement *position_element = new TiXmlElement("Position");
	position_element->SetAttribute("x", gameobject->transform->getPosition().x);
	position_element->SetAttribute("y", gameobject->transform->getPosition().y);

	//add position to transform and add transform to gameobject
	transform_element->LinkEndChild(position_element);
	gameobject_element->LinkEndChild(transform_element);

	//add gameobject and declaration to document
	xml_document.LinkEndChild(gameobject_element);
	
	//actually save to disk and create the xml file in current directory
	xml_document.SaveFile("dynamic_gameobject.xml");
}

void read_gameobject_xml() {
	TiXmlDocument document("test_gameobject.xml");
	bool did_load = document.LoadFile();

	if (!did_load) {
		Debug::print("didnt load shit");
		return;
	}

	GameObject* gameobject = new GameObject("ERROR LOADING XML NAME", nullptr);

	TiXmlElement *gameobject_element = document.FirstChildElement();
	//position is child of transform which is first child of gameobject
	TiXmlElement *position = gameobject_element->FirstChildElement()->FirstChildElement();

	gameobject->name = gameobject_element->Attribute("name");
	gameobject->transform->setPosition(std::stof(position->Attribute("x")), std::stof(position->Attribute("y")));

	//loop thru rest of component elements
	for (TiXmlElement *xml_element = gameobject_element->FirstChildElement()->NextSiblingElement();
					xml_element != nullptr; xml_element = xml_element->NextSiblingElement()) {

		std::cout << xml_element->Value() << std::endl;
		//for some reason this acts like contains key and returns 0 or 1 so basically a bool
		if (derp.count(xml_element->Value())) {
			derp.find(xml_element->Value())->second(xml_element, gameobject);
		}
	}

	//read all the data from the gameobject to make sure it worked
	std::cout << gameobject->name << "\n" << "X: " << gameobject->transform->getPosition().x << " Y: " 
											<< gameobject->transform->getPosition().y << "\n" << std::endl;
	std::cout << "Mass: " << gameobject->get_component<Rigidbody>()->mass << std::endl;
}

int main(){

	derp.insert(std::pair<std::string, set_component_from_xml*>("Rigidbody", Rigidbody::set_component_from_xml));

	//derp.find("Rigidbody")->second(new TiXmlElement("test"), new GameObject("some object", nullptr));

	//if (derp.count("Rigidbody") == false) {
	//	Debug::print("it worked!");
	//}

	//DerpEngine application;
	//application.main_loop();
	//application.

	//build_simple_doc();

	//GameObject *test_object = new GameObject("plz work", nullptr);

	//if (typeid(derp) == typeid(GameObject)) {
		//std::cout << "it worked!" << std::endl;
	//}

	//test_object->transform->setPosition(1337, 69);
	//build_gameobject_xml(test_object);

	//dump_to_stdout("test_gameobject.xml");

	read_gameobject_xml();

	system("pause");

	return 0;
}