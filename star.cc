#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/mobility-module.h"

using namespace ns3;

int main ()
{
NodeContainer center;
center.Create(1);

NodeContainer leaves;
leaves.Create(19);

NodeContainer allNodes;
allNodes.Add(center);
allNodes.Add(leaves);

InternetStackHelper stack;
stack.Install(allNodes);

PointToPointHelper p2p;
p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
p2p.SetChannelAttribute("Delay", StringValue("2ms"));

for (uint32_t i=0;i<19;i++)
{
NodeContainer pair(center.Get(0), leaves.Get(i));
p2p.Install(pair);
}

MobilityHelper mobility;
mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
mobility.Install(allNodes);

AnimationInterface anim("star.xml");

anim.SetConstantPosition(center.Get(0), 50, 50);

for(uint32_t i=0;i<19;i++)
{
anim.SetConstantPosition(leaves.Get(i), 20 + i*5 , 10 + (i%5)*20);
}

Simulator::Stop(Seconds(10));
Simulator::Run();
Simulator::Destroy();

return 0;
}
