#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

int main ()
{
NodeContainer root;
root.Create(1);

NodeContainer level1;
level1.Create(4);

NodeContainer level2;
level2.Create(16);

NodeContainer allNodes;
allNodes.Add(root);
allNodes.Add(level1);
allNodes.Add(level2);

InternetStackHelper stack;
stack.Install(allNodes);

PointToPointHelper p2p;
p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
p2p.SetChannelAttribute("Delay", StringValue("2ms"));

/* root -> level1 */

for(int i=0;i<4;i++)
{
NodeContainer pair(root.Get(0), level1.Get(i));
p2p.Install(pair);
}

/* level1 -> level2 */

int index = 0;

for(int i=0;i<4;i++)
{
for(int j=0;j<4;j++)
{
NodeContainer pair(level1.Get(i), level2.Get(index));
p2p.Install(pair);
index++;
}
}

AnimationInterface anim("tree.xml");

/* ---- Set clean tree positions ---- */

anim.SetConstantPosition(root.Get(0),50,10);

/* level 1 */

anim.SetConstantPosition(level1.Get(0),20,30);
anim.SetConstantPosition(level1.Get(1),40,30);
anim.SetConstantPosition(level1.Get(2),60,30);
anim.SetConstantPosition(level1.Get(3),80,30);

/* level 2 */

int posX = 10;

for(int i=0;i<16;i++)
{
anim.SetConstantPosition(level2.Get(i),posX,60);
posX +=5;
}

/* ------------------------------ */

Simulator::Stop(Seconds(10));
Simulator::Run();
Simulator::Destroy();

return 0;
}
