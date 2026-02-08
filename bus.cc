#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

int main() {
    NodeContainer nodes;
    nodes.Create(18);

    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

    csma.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    AnimationInterface anim("bus.xml");

    Simulator::Run();
    Simulator::Destroy();
}
