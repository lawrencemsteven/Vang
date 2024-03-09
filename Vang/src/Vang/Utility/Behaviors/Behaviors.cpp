#include "Vang.h"
#include "./Vang/PugiXML/pugixml.hpp"
#include "Behaviors.h"

namespace Vang::Utility::Behaviors {

	BehaviorTree::BehaviorTree(std::string xml_path) {
		pugi::xml_parse_result result =
			tree.load_file(static_cast<std::string>(VANG_XML_FOLDER).append("/test.xml").c_str());

		if (!result) {
			std::cout << "Parse error: " << result.description()
					  << ", character pos= " << result.offset << std::endl;
		}

		current_xml_node	  = tree.first_child().first_child().first_child();
		current_behavior_node = createBehaviorNodeFromXML(current_xml_node);
		current_status		  = Vang::Utility::Behaviors::NodeStatus::SUCCESS;
	}

	void BehaviorTree::update() {
		if (current_status == FAILURE) {
			return;
		}

		if (current_status != RUNNING) {
			current_status = current_behavior_node->onStart();
		}
		else {
			current_status = current_behavior_node->onRunning();
		}

		if (current_status == SUCCESS) {
			if (current_xml_node != current_xml_node.next_sibling()) {
				current_xml_node = current_xml_node.next_sibling();
			}
			else {
				current_xml_node = current_xml_node.parent().next_sibling();
			}

			current_behavior_node = createBehaviorNodeFromXML(current_xml_node);
		}
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
		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}

	NodeStatus WaitBehavior::onRunning() {
		playerPosition	   = Vang::getPlayer().getCamera().getPosition();
		entityPosition	   = Vang::getEntityManager().getEntity(0).getPosition();
		distanceFromPlayer = glm::distance(playerPosition, entityPosition);

		if (distanceFromPlayer <= triggerDistance) {
			return Vang::Utility::Behaviors::NodeStatus::SUCCESS;
		}

		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}

	NodeStatus PursueBehavior::onStart() {
		moveSpeed = 0.1f;
		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}

	NodeStatus PursueBehavior::onRunning() {
		playerPosition = Vang::getPlayer().getCamera().getPosition();
		entityPosition = Vang::getEntityManager().getEntity(0).getPosition();
		lerpPosition   = glm::mix(entityPosition, playerPosition, moveSpeed);
		Vang::getEntityManager().getEntity(0).setPosition(lerpPosition);

		return Vang::Utility::Behaviors::NodeStatus::RUNNING;
	}
}