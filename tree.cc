#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main() {
    NodeContainer nodes;
    nodes.Create(20);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    InternetStackHelper stack;
    stack.Install(nodes);

    AnimationInterface anim("tree.xml");

    int parent = 0;
    int child = 1;

    while (child < 20) {
        NodeContainer pair(nodes.Get(parent), nodes.Get(child));
        p2p.Install(pair);

        child++;
        if (child < 20) {
            NodeContainer pair2(nodes.Get(parent), nodes.Get(child));
            p2p.Install(pair2);
            child++;
        }
        parent++;
    }

    Simulator::Run();
    Simulator::Destroy();
}
