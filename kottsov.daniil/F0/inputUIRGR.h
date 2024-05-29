#include<iostream>
#include"GraphRGR.h"
#include<string>

#ifndef UI
#define UI

template<typename Weight=int>
struct NumberIO
{
  Weight&ref;
};
template<typename Node>
struct NodeIO
{
  Node &ref;
};
template<typename Weight=int>
std::istream& operator>>(std::istream& in,NumberIO<Weight>&& num)
{
  std::istream::sentry ward(in);
  if(!ward)
  {
    std::cerr<<"istream failure\n";
    return in;
  }
  in>>num.ref;
  return in;
}
template<typename Node>
std::istream& operator>>(std::istream& in,NodeIO<Node>&& node)
{
  std::istream::sentry ward(in);
  if(!ward)
  {
    std::cerr<<"istream failure\n";
    return in;
  }
  in>>node.ref;
  return in;
}
template<typename Node,typename Weight=int>
bool inputUI(Graph<Node,Weight>& graph,std::ostream& out,std::istream& in)
{
  std::istream::sentry ward(in);
  if(!ward&&in.eof())
  {
    out<<"finishing...\n";
    return 1;
  }
  else if(!ward)
  {
    std::cerr<<"istream failure\n";
    return 1;
  }
  std::ostream::sentry sentry(out);
  if(!sentry)
  {
    std::cerr<<"ostreamfailure\n";
    return 1;
  }
  using stringIO=NodeIO<std::string>;
  std::string command;
  in>>stringIO{command};
  if(!in)
  {
    std::cin.setstate(std::ios::failbit);
    std::cerr<<"ERR.INVALIDINPUT\n";
    return 0;
  }
  if(command=="HELP")
  {
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    out<<"GET_GRAPH:"<<"print graph to standart output\n";
    out<<"ADD_NODE NAME:"<<"insert a new node with a name NAME\n";
    out<<"ADD_BRANCH NODE_START NODE_END:";
    out<<"insert a branch from NODE_START to NODE_END\n";
    out<<"REM_NODE NAME:"<<"remove the node with NAME name\n";
    out<<"REM_BRANCH NODE_START NODE_END:";
    out<<"remove a branch from NODE_START to NODE_END\n";
    out<<"EXISTS_NODE NAME:"<<"returnswhetheranodewithNAMEnameexists\n";
    out<<"EXISTS_BRANCH NODE_START NODE_END:";
    out<<"returns whether a branch exists from NODE_START to NODE_END\n";
    out<<"REMOVE_CYCLES:"<<"removes cycles and parallel branches\n";
    out<<"GET_DEGREES NAME:"<<"prints all 3 degrees of the node\n";
    out<<"GET_MAX_DEG:"<<"returns all 3 max degrees in the graph";
    out<<"(if 2 or more have the biggest degree returns first occurence)\n";
    out<<"GET_DELTAS:"<<"returns nodes that have only incoming branches\n";
    out<<"GET_SOURCES:"<<"returns nodes that have only outcoming branches\n";
    out<<"HELP:"<<"shows this info\n";
    out<<"DONE\n";
    return 0;
  }
  else if(command=="GET_GRAPH")
  {
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      try
      {
        graph.print(out);
        out<<"DONE\n";
      }
      catch(const std::out_of_range &ex)
      {
        std::cerr<<"ERR."<<ex.what()<<'\n';
        return 0;
      }
    }
    catch(const std::ios_base::failure& err)
    {
      std::cerr<<err.what()<<'\n';
      std::cerr<<"FATAL ERROR:OSTREAM FAILURE\n";
      return 1;
    }
    return 0;
  }
  else if(command=="ADD_NODE")
  {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    Node name;
    in>>NodeIO<Node>{name};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      graph.insertNode(name);
      out<<"DONE\n";
    }
    catch(const std::invalid_argument& err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="ADD_BRANCH")
  {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    Node start;
    Node end;
    in>>NodeIO<Node>{start};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    in>>NodeIO<Node>{end};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      graph.insertBranch(start,end);
      out<<"DONE\n";
    }
    catch(const std::out_of_range& err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="REM_NODE")
  {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    Node node;
    in>>NodeIO<Node>{node};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      try
      {
        graph.removeNode(node);
        out<<"DONE\n";
      }
      catch(const std::invalid_argument &err)
      {
        std::cerr<<"ERR.\n"<<err.what()<<'\n';
        std::cin.setstate(std::ios::failbit);
        return 0;
      }
    }
    catch(const std::out_of_range &ex)
    {
      std::cerr<<"ERR.\n"<<ex.what()<<"\n";
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="REM_BRANCH")
  {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    Node start;
    Node end;
    in>>NodeIO<Node>{start};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    in>>NodeIO<Node>{end};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      try
      {
        graph.removeBranch(start,end);
        out<<"DONE\n";
      }
      catch(const std::invalid_argument &ex)
      {
        std::cerr<<"ERR.\n"<<ex.what()<<'\n';
        std::cin.setstate(std::ios::failbit);
        return 0;
      }
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="EXISTS_NODE")
  {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    Node node;
    in>>NodeIO<Node>{node};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      if(graph.existsNode(node))
      {
        out<<"YES\n";
      }
      else
      {
        out<<"NO\n";
      }
      out<<"DONE\n";
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="EXISTS_BRANCH")
  {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    Node start;
    Node end;
    in>>NodeIO<Node>{start};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()=='\n')
    {
      std::cerr<<"NOT ENOUGH ARGUMENTS\n";
      return 0;
    }
    in>>NodeIO<Node>{end};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALID ARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      if(graph.existsBranch(start,end))
      {
        out<<"YES\n";
      }
      else
      {
        out<<"NO\n";
      }
      out<<"DONE\n";
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="REMOVE_CYCLES")
  {
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      graph.removeCycles();
      out<<"DONE\n";
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="GET_DEGREES")
    {
    if(in.peek()=='\n')
    {
      std::cerr<<"NOTENOUGHARGUMENTS\n";
      return 0;
    }
    Node node;
    in>>NodeIO<Node>{node};
    if(!in)
    {
      std::cin.setstate(std::ios::failbit);
      std::cerr<<"ERR.INVALIDARGUMENT\n";
      return 0;
    }
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      try
      {
        out<<"total:"<<graph.totalDegree(node);
        out<<"in:"<<graph.inDegree(node);
        out<<"out:"<<graph.outDegree(node);
        out<<"\nDONE\n";
      }
      catch(const std::invalid_argument &ex)
      {
        std::cerr<<"ERR.\n"<<ex.what()<<'\n';
        std::cin.setstate(std::ios::failbit);
        return 0;
      }
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="GET_MAX_DEG")
  {
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      try
      {
        auto a=graph.maxDegree(0);
        auto b=graph.maxDegree(-1);
        auto c=graph.maxDegree(1);
        out<<"total:"<<std::get<0>(a)<<':'<<std::get<1>(a);
        out<<"in:"<<std::get<0>(b)<<':'<<std::get<1>(b);
        out<<"out:"<<std::get<0>(c)<<':'<<std::get<1>(c);
        out<<"\nDONE\n";
      }
      catch(const std::invalid_argument &ex)
      {
        std::cerr<<"ERR.\n"<<ex.what()<<'\n';
        std::cin.setstate(std::ios::failbit);
        return 0;
      }
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="GET_DELTAS")
  {
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      out<<"Deltas:";
      graph.deltas(out);
      out<<'\n';
      out<<"DONE\n";
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else if(command=="GET_SOURCES")
  {
    if(in.peek()!='\n')
    {
      std::cerr<<"INVALID_CMD\n";
      return 0;
    }
    try
    {
      out<<"Sources:";
      graph.sources(out);
      out<<'\n';
      out<<"DONE\n";
    }
    catch(const std::out_of_range &err)
    {
      std::cerr<<"ERR.\n"<<err.what()<<'\n';
      std::cin.setstate(std::ios::failbit);
      return 0;
    }
    return 0;
  }
  else
  {
    std::cerr<<"INVALIDCMD\n";
    std::cin.setstate(std::ios::failbit);
    return 0;
  }
  out<<"DONE\n";
  return 0;
}
#endif
