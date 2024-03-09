#include <Vang.h>
#include "./Vang/PugiXML/pugixml.hpp"

namespace Vang::Utility::Behaviors {

    enum NodeStatus {
        SUCCESS,
        RUNNING,
        FAILURE
    };

    class BehaviorNode {
        public:
            BehaviorNode() {};

            virtual NodeStatus onStart() = 0;

            virtual NodeStatus onRunning() = 0;
    };

    class WaitBehavior : public BehaviorNode {
        public:
            WaitBehavior() {};

            NodeStatus onStart() override;

            NodeStatus onRunning() override;

        private:
            float distanceFromPlayer;
            float triggerDistance;
            glm::vec3 playerPosition;
            glm::vec3 entityPosition;
    };

    class PursueBehavior : public BehaviorNode {
        public:
            PursueBehavior() {};

            NodeStatus onStart() override;

            NodeStatus onRunning() override;

        private:
            float moveSpeed;
            glm::vec3 playerPosition;
            glm::vec3 entityPosition;
            glm::vec3 lerpPosition;
    };

    class BehaviorTree {
        public:
            BehaviorTree(std::string xml_path);

            void update();

            BehaviorNode* createBehaviorNodeFromXML(pugi::xml_node node);

        private:
            pugi::xml_document tree;
            pugi::xml_node current_xml_node;
            BehaviorNode* current_behavior_node;
            NodeStatus current_status;
    };
}