/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Strasbourg
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Pierre Weiss <3weissp@gmail.com>
 */

//  Topology Generated :
//
//              (*)-PC
// AP --((*))   (*)-PC
//              (*)-PC
//

using namespace std;

#include <cstdlib>
#include <iostream>

#include "../generator.h"
#include "../ap.h"

int main(int argc, char *argv[])
{
  /* avoid compile warnings */
  argc = argc;
  argv = argv;
  
  Generator *gen = new Generator(std::string("example-wifi-ap"));
  
  /* Add Node : */
  gen->AddNode("Ap");//0
  gen->AddNode("Station");//1
  gen->AddNode("Station");//2
  gen->AddNode("Station");//3
  
  /* Add the bridge. */
  gen->AddNetworkHardware("Ap", gen->GetNode(0)->GetNodeName());
  Ap *ap = dynamic_cast<Ap*>(gen->GetNetworkHardware(0));
  ap->SetMobility(true);
  gen->GetNetworkHardware(0)->Install(gen->GetNode(1)->GetNodeName());
  gen->GetNetworkHardware(0)->Install(gen->GetNode(2)->GetNodeName());
  gen->GetNetworkHardware(0)->Install(gen->GetNode(3)->GetNodeName());
  
  /* Enable trace... */
  gen->GetNetworkHardware(0)->SetTrace(true);
  
  /* Add an application */
  gen->AddApplication("Ping", gen->GetNode(1)->GetNodeName(), gen->GetNode(2)->GetNodeName(), 0, 5);// 0 start time - 5 end time

  gen->GenerateCodeCpp();
  
  delete ap;
  delete gen;
}
