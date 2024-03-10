#include "Vang.h"
#include "./Vang/PugiXML/pugixml.hpp"
#include "Behaviors.h"
#include "glm/ext.hpp"

namespace Vang::Utility::Behaviors {

	BehaviorTree::BehaviorTree(std::string xml_path) {
		pugi::xml_parse_result result =
			tree.load_file(static_cast<std::string>(VANG_XML_FOLDER).append("/BasicEntity.xml").c_str());

		if (!result) {
			std::cout << "Parse error: " << result.description()
					  << ", character pos= " << result.offset << std::endl;
		}

		current_xml_node	  = tree.first_child().first_child().first_child();
		current_behavior_node = createBehaviorNodeFromXML(current_xml_node);
		current_status		  = Vang::Utility::Behaviors::NodeStatus::SUCCESS;

		std::cout << "tree initialized" << std::endl;
	}

	void BehaviorTree::update() {
		if (current_status == FAILURE) {
			std::cout << "failure node status" << std::endl;
			return;
		}

		if (current_status != RUNNING) {
			std::cout << "not running node status" << std::endl;
			current_status = current_behavior_node->onStart();
		}
		else {
			std::cout << "running node status" << std::endl;
			current_status = current_behavior_node->onRunning();
		}

		if (current_status == SUCCESS) {
			std::cout << "successful node status" << std::endl;
			if (current_xml_node != current_xml_node.next_sibling()) {
				current_xml_node = current_xml_node.next_sibling();
			}
			else {
				current_xml_node = current_xml_node.parent().next_sibling();
			}

			current_behavior_node = createBehaviorNodeFromXML(current_xml_node);
		}

		std::cout << "tree updating" << std::endl;
	}

	BehaviorNode* BehaviorTree::createBehaviorNodeFromXML(pugi::xml_node node) {
		if (strcmp(node.name(), "Sequence") == 0) {
			return createBehaviorNodeFromXML(node.first_child());
		}

		else if (strcmp(node.name(), "Pursue") == 0) {
			return new PursueBehavior();
		}

		else if (strcmp(node.name(), "Wait") == 0) {
			return new WaitBehavior();
		}

		// cout << "Error: could not find behavior for " << node.name() << endl;
		current_status = Vang::Utility::Behaviors::NodeStatus::FAILURE;
		return NULL;
	}

	NodeStatus WaitBehavior::onStart() {
		triggerDistance = 5.0f;
		Vang::getEntityManager().createEntity(glm::vec4(5.0f, 5.0f, 5.0f, 0.0f), 1.0f);
		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}

	NodeStatus WaitBehavior::onRunning() {
		if (Vang::getEntityManager().getEntities().size() <= 0)
		{
			return Vang::Utility::Behaviors::NodeStatus::FAILURE;
		}

		playerPosition	   = Vang::getPlayer().getCamera().getPosition();
		std::cout << Vang::getEntityManager().getEntities().size() << std::endl;
		entityPosition	   = Vang::getEntityManager().getEntity(0).getPosition();
		distanceFromPlayer = glm::distance(playerPosition, entityPosition);

		std::cout << "Entity: " << glm::to_string(entityPosition) << std::endl;
		std::cout << "Player: " << glm::to_string(playerPosition) << std::endl;

		if (distanceFromPlayer <= triggerDistance) {
			return Vang::Utility::Behaviors::NodeStatus::SUCCESS;
		}

		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}

	NodeStatus PursueBehavior::onStart() {
		moveSpeed = 2.0f;
		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}

	NodeStatus PursueBehavior::onRunning() {
		playerPosition = Vang::getPlayer().getCamera().getPosition();
		entityPosition = Vang::getEntityManager().getEntity(0).getPosition();

		const glm::vec3 distance = playerPosition - entityPosition;
		glm::vec3 direction = glm::normalize(distance);
		if (distance == glm::vec3(0.0f, 0.0f, 0.0f))
		{
			direction = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		const glm::vec3 entityDisplacement = direction * moveSpeed * Vang::Utility::Time::deltaTime();

		glm::vec3 newEntityPosition = entityPosition + entityDisplacement;

		Vang::getEntityManager().getEntity(0).setPosition(newEntityPosition);

		std::cout << "Entity: " << glm::to_string(entityPosition) << std::endl;
		std::cout << "Player: " << glm::to_string(playerPosition) << std::endl;

		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}
}