#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main ()
{
NodeContainer nodes;
nodes.Create(20); // 5x4 grid

InternetStackHelper stack;
stack.Install(nodes);

PointToPointHelper p2p;
p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
p2p.SetChannelAttribute("Delay", StringValue("2ms"));

/* horizontal connections */

for(int row=0; row<4; row++)
{
for(int col=0; col<4; col++)
{
int n1 = row*5 + col;
int n2 = row*5 + col + 1;

NodeContainer pair(nodes.Get(n1), nodes.Get(n2));
p2p.Install(pair);
}
}

/* vertical connections */

for(int col=0; col<5; col++)
{
for(int row=0; row<3; row++)
{
int n1 = row*5 + col;
int n2 = (row+1)*5 + col;

NodeContainer pair(nodes.Get(n1), nodes.Get(n2));
p2p.Install(pair);
}
}

AnimationInterface anim("grid.xml");

/* place nodes in grid */

int index = 0;

for(int row=0; row<4; row++)
{
for(int col=0; col<5; col++)
{
anim.SetConstantPosition(nodes.Get(index), 20 + col*15, 20 + row*15);
index++;
}
}

Simulator::Stop(Seconds(10));
Simulator::Run();
Simulator::Destroy();

return 0;
}
