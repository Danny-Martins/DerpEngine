#include "Scene.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"
#include "BoxCollider.hpp"

#include <string>
#include <map>

typedef void set_component_from_xml(TiXmlElement*, GameObject*);
typedef std::map<std::string, set_component_from_xml*> ComponentMap;

ComponentMap component_map;

GameObject* Scene::scene_root;

Scene::Scene() {
	Scene::scene_root = nullptr;
	Scene::scene_root = new GameObject("SCENE ROOT", nullptr);
}

Scene::~Scene() {
	this->shutdown();
}

void Scene::build_scene_from_xml() {
	component_map.insert(std::pair<std::string, set_component_from_xml*>("Rigidbody", Rigidbody::set_component_from_xml));
	component_map.insert(std::pair<std::string, set_component_from_xml*>("SpriteRenderer", SpriteRenderer::set_component_from_xml));
	component_map.insert(std::pair<std::string, set_component_from_xml*>("BoxCollider", BoxCollider::set_component_from_xml));

	TiXmlDocument document("..\\Assets\\Scenes\\Gameplay.xml");
	bool did_load = document.LoadFile();

	if (!did_load) {
		Debug::print("didnt load shit");
		return;
	}

	//loop thru all gameobjects in scene
	for (TiXmlElement *gameobject_element = document.FirstChildElement()->FirstChildElement(); gameobject_element != nullptr;
											gameobject_element = gameobject_element->NextSiblingElement()) {

		GameObject* gameobject = new GameObject("ERROR LOADING XML NAME", nullptr);

		//position is child of transform which is first child of gameobject
		TiXmlElement *position = gameobject_element->FirstChildElement()->FirstChildElement();
		TiXmlElement *scale = position->NextSiblingElement()->NextSiblingElement();

		gameobject->name = gameobject_element->Attribute("name");
		gameobject->transform->setPosition(std::stof(position->Attribute("x")), std::stof(position->Attribute("y")));
		gameobject->transform->setScale(std::stof(scale->Attribute("x")), std::stof(scale->Attribute("y")));

		//loop thru rest of component elements
		for (TiXmlElement *xml_element = gameobject_element->FirstChildElement()->NextSiblingElement();
			xml_element != nullptr; xml_element = xml_element->NextSiblingElement()) {

			//for some reason this acts like contains key and returns 0 or 1 so basically a bool
			if (component_map.count(xml_element->Value())) {
				component_map.find(xml_element->Value())->second(xml_element, gameobject);
			}
		}

	}
	
}

void Scene::shutdown() {
	//for (std::vector<GameObject*>::iterator itorator = this->scene_graph.begin(); itorator != this->scene_graph.end(); itorator++) {
		//delete (*itorator);
	//}
}
/*
void Scene::add_to_graph(GameObject* gameobject) {
	this->scene_graph.push_back(gameobject);
	std::cout << "Added " << gameobject->name << " to scene root" << std::endl;
	std::cout << scene_graph.size() << std::endl;
}
*/
/*
void Scene::start() {
	for (std::vector<GameObject*>::iterator itorator = this->scene_graph.begin(); itorator != this->scene_graph.end(); itorator++) {
		(*itorator)->start();
	}
}
*/
/*
void Scene::update(float delta_time) {
	for (std::vector<GameObject*>::iterator itorator = this->scene_graph.begin(); itorator != this->scene_graph.end(); itorator++) {
		(*itorator)->update(delta_time);
	}
}
*/
