#include "./Vang/PugiXML/pugixml.hpp"

using namespace std;
using namespace pugi;

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

    class PrintBehavior : public BehaviorNode {
        public:
            PrintBehavior(const string msg) : message(msg) {};

            NodeStatus onStart() override;

            NodeStatus onRunning() override;

        private:
            const string message;
    };

    class WaitBehavior : public BehaviorNode {
        public:
            WaitBehavior(const float t) : time(t) {};

            NodeStatus onStart() override;

            NodeStatus onRunning() override;

        private:
            float time;
            float currentTime;
    };

    class BehaviorTree {
        public:
            BehaviorTree(std::string xml_path);

            void update();

            BehaviorNode* createBehaviorNodeFromXML(xml_node node);

        private:
            xml_document tree;
            xml_node current_xml_node;
            BehaviorNode* current_behavior_node;
            NodeStatus current_status;
    };
}