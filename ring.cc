#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main() {
    NodeContainer nodes;
    nodes.Create(15);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    InternetStackHelper stack;
    stack.Install(nodes);

    AnimationInterface anim("ring.xml");

    for (int i = 0; i < 14; i++) {
        NodeContainer pair(nodes.Get(i), nodes.Get(i+1));
        p2p.Install(pair);
    }

    NodeContainer last(nodes.Get(14), nodes.Get(0));
    p2p.Install(last);

    Simulator::Run();
    Simulator::Destroy();
}
