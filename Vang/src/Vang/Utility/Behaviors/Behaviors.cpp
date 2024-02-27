#include "./Vang/PugiXML/pugixml.hpp"
#include "Behaviors.h"

using namespace std;
using namespace pugi;

namespace Vang::Utility::Behaviors {

    BehaviorTree::BehaviorTree(string xml_path) {
        xml_parse_result result = tree.load_file("test.xml");

        if (!result)
        {
            cout << "Parse error: " << result.description() << ", character pos= " << result.offset << endl;
        }

        current_xml_node = tree.first_child().first_child().first_child();
        current_behavior_node = createBehaviorNodeFromXML(current_xml_node);
        current_status = SUCCESS;
    }

    void BehaviorTree::update() {
        if (current_status == FAILURE)
        {
            return;
        }

        if (current_status != RUNNING)
        {
            current_status = current_behavior_node->onStart();
        }
        else
        {
            current_status = current_behavior_node->onRunning();
        }

        if (current_status == SUCCESS)
        {
            if (current_xml_node != current_xml_node.next_sibling())
            {
                current_xml_node = current_xml_node.next_sibling();
            }
            else
            {
                current_xml_node = current_xml_node.parent().next_sibling();
            }

            current_behavior_node = createBehaviorNodeFromXML(current_xml_node);
        }
    }

    BehaviorNode* BehaviorTree::createBehaviorNodeFromXML(xml_node node)
    {
        if (strcmp(node.name(),"Sequence") == 0)
        {
            return createBehaviorNodeFromXML(node.first_child());
        }

        else if (strcmp(node.name(),"Print") == 0)
        {
            return new PrintBehavior(node.attribute("str").value());
        }

        else if (strcmp(node.name(),"Wait") == 0)
        {
            return new WaitBehavior(node.attribute("time").as_float());
        }

        //cout << "Error: could not find behavior for " << node.name() << endl;
        current_status = FAILURE;
        return NULL;
    }

    NodeStatus PrintBehavior::onStart()
    {
        cout << message << endl;
        return SUCCESS;
    }

    NodeStatus PrintBehavior::onRunning()
    {
        return SUCCESS;
    }

    NodeStatus WaitBehavior::onStart()
    {
        currentTime = time;
        return RUNNING;
    }

    NodeStatus WaitBehavior::onRunning()
    {
        currentTime -= 1;
        
        if (currentTime <= 0)
        {
            return SUCCESS;
        }

        return RUNNING;
    }
}