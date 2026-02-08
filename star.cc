#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main() {
    NodeContainer central;
    central.Create(1);

    NodeContainer leaves;
    leaves.Create(15);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    InternetStackHelper stack;
    stack.Install(central);
    stack.Install(leaves);

    AnimationInterface anim("star.xml");

    for (int i = 0; i < 15; i++) {
        NodeContainer pair(central.Get(0), leaves.Get(i));
        p2p.Install(pair);
    }

    Simulator::Run();
    Simulator::Destroy();
}
