#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include <cmath>

using namespace ns3;

int main ()
{
    NodeContainer nodes;
    nodes.Create(20);

    InternetStackHelper stack;
    stack.Install(nodes);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    /* Create ring connections */
    for (int i = 0; i < 19; i++)
    {
        NodeContainer pair(nodes.Get(i), nodes.Get(i+1));
        p2p.Install(pair);
    }

    /* connect last node back to first */
    NodeContainer last(nodes.Get(19), nodes.Get(0));
    p2p.Install(last);

    AnimationInterface anim("ring.xml");

    /* ---- force circular layout ---- */
    double radius = 30.0;
    double centerX = 50.0;
    double centerY = 50.0;

    for (uint32_t i = 0; i < nodes.GetN(); i++)
    {
        double angle = 2 * M_PI * i / nodes.GetN();
        double x = centerX + radius * cos(angle);
        double y = centerY + radius * sin(angle);

        anim.SetConstantPosition(nodes.Get(i), x, y);
    }
    /* -------------------------------- */

    Simulator::Stop(Seconds(10));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
