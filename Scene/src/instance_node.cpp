#include "instance_node.hpp"
#include "scene.hpp"

void InstanceNode::preRender() {
	SceneNode::preRender();

	Scene* scene = Scene::getInstance();

	std::shared_ptr<Model> m = scene->getModel(objPath);
	if (!m) {
		m = std::make_shared<Model>(objPath, shaders);
		scene->addModel(objPath, m);
	}
}

void InstanceNode::render() {
	Scene* scene = Scene::getInstance();

	std::shared_ptr<Model> model = scene->getModel(objPath);
	const glm::mat4x4& pv = scene->getPVMatrix();
	model->setTransforms(transforms);
	model->draw(pv);
}