#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"

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

for(int i=0;i<19;i++)
{
NodeContainer pair(nodes.Get(i), nodes.Get(i+1));
p2p.Install(pair);
}


MobilityHelper mobility;

mobility.SetPositionAllocator(
"ns3::GridPositionAllocator",
"MinX", DoubleValue(0.0),
"MinY", DoubleValue(0.0),
"DeltaX", DoubleValue(10.0),
"DeltaY", DoubleValue(0.0),
"GridWidth", UintegerValue(20),
"LayoutType", StringValue("RowFirst"));

mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
mobility.Install(nodes);

/* -------------------------------------- */

AnimationInterface anim("bus.xml");

Simulator::Stop(Seconds(10));
Simulator::Run();
Simulator::Destroy();

return 0;
}
