#include <iostream>
#include <limits>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <exception>
#include <iterator>
#include <numeric>
#include <functional>

#ifndef GRAPH
#define GRAPH
namespace rgr
{
template <typename Node, typename Weight = int>
class Graph
{
  private:
    std::vector<std::vector<std::pair<Weight,Weight>>> array_;
    std::vector<Node> nodes_;
    size_t nodesCount_;
    size_t index(const Node& node);
    void DFSR(size_t startingIndex, size_t currentIndex);
  public:
    Graph();
    Graph(const Graph<Node,Weight>& other);
    Graph<Node,Weight>& operator=(const Graph<Node,Weight>& other);
    Graph(Graph<Node,Weight>&& other);
    bool existsNode(const Node& value);
    bool existsBranch(const Node& first, const Node& second);
    void insertNode(const Node& value);
    void insertBranch(const Node& first, const Node& second);
    void removeBranch(const Node& first, const Node& second);
    void removeNode(const Node& node);
    void print(std::ostream& out);
    Weight totalDegree(const Node& node);
    Weight inDegree(const Node& node);
    Weight outDegree(const Node& node);
    std::pair<Node,Weight> maxDegree(short int param);
    void removeCycles();
    void sources(std::ostream& out);
    void deltas(std::ostream& out);
};
template <typename Node, typename Weight>
Graph<Node,Weight>::Graph()
{
  array_ = std::vector<std::vector<std::pair<Weight,Weight>>>(0);
  nodes_ = std::vector<Node>(0);
  nodesCount_ = 0;
}
template <typename Node, typename Weight>
Graph<Node, Weight>::Graph(const Graph<Node, Weight>& other)
{
  array_ = std::vector<std::vector<std::pair<Weight,Weight>>>(other.nodesCount_);
  for (size_t i = 0; i < other.nodesCount_; i++)
  {
    array_[i] = std::vector<std::pair<Weight,Weight>>(other.nodesCount_);
    std::copy(other.array_[i].begin(),other.array_[i].end(),std::back_inserter(array_[i]));
  }
  nodes_ = std::vector<Node>(other.nodesCount_);
  std::copy(other.nodes_.begin(),other.nodes_.end(),std::back_inserter(nodes_));
  nodesCount_ = other.nodesCount_;
}
template <typename Node, typename Weight>
Graph<Node, Weight>& Graph<Node, Weight>::operator=(const Graph<Node, Weight>& other)
{
  array_ = std::vector<std::vector<std::pair<Weight,Weight>>>(other.nodesCount_);
  for (size_t i = 0; i < other.nodesCount_; i++)
  {
    array_[i] = std::vector<std::pair<Weight,Weight>>(nodesCount_);
    std::copy(other.array_[i].begin(),other.array_[i].end(),std::back_inserter(array_[i]));
  }
  nodes_ = std::vector<Node>(other.nodesCount_);
  std::copy(other.nodes_.begin(),other.nodes_.end(),std::back_inserter(nodes_));
  nodesCount_ = other.nodesCount_;
  return *this;
}
template <typename Node, typename Weight>
Graph<Node, Weight>::Graph(Graph<Node, Weight>&& other)
{
  array_ = std::move(other.array_);
  nodes_ = std::move(other.nodes_);
  nodesCount_ = other.nodesCount_;
  other.array_.clear();
  other.nodes_.clear();
  other.array_.shrink_to_fit();
  other.nodes_.shrink_to_fit();
  other.nodesCount_ = 0;
}
template <typename Node, typename Weight>
size_t Graph<Node,Weight>::index(const Node& node)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return std::numeric_limits<size_t>::max();
  }
  auto index = std::find(nodes_.begin(),nodes_.end(),node);
  if (index!=std::end(nodes_))
  {
    return std::distance(nodes_.begin(),index);
  }
  return std::numeric_limits<size_t>::max();
}
template <typename Node, typename Weight>
bool Graph<Node,Weight>::existsNode(const Node& value)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return false;
  }
  auto index = std::find(nodes_.begin(),nodes_.end(),value);
  if (index!=std::end(nodes_))
  {
    return true;
  }
  return false;
}
template <typename Node, typename Weight>
bool Graph<Node, Weight>::existsBranch(const Node& first, const Node& second)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return false;
  }
  size_t start = index(first);
  if (start >= nodesCount_)
  {
    throw std::out_of_range("first node doesn't exist");
    return false;
  }
  size_t end = index(second);
  if (end >= nodesCount_)
  {
    throw std::out_of_range("second node doesn't exist");
    return false;
  }
  if (start == end)
  {
    return (std::get<1>(array_[start][end]) > 0);
  }
  else if (std::get<1>(array_[start][end]) > 0 && std::get<0>(array_[end][start]) < 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
template <typename Node, typename Weight>
void Graph<Node,Weight>::insertNode(const Node& value)
{
  if (array_.size() == 0)
  {
    array_.push_back(std::vector<std::pair<Weight,Weight>>(1));
    array_[0][0] = std::make_pair(0,0);
    nodes_.push_back(value);
    nodesCount_++;
    return;
  }
  if (existsNode(value))
  {
    throw std::invalid_argument("Node already exists");
    return;
  }
  nodesCount_++;
  array_.push_back(std::vector<std::pair<Weight,Weight>>(nodesCount_));
  for (size_t i = 0; i < (nodesCount_-1);i++)
  {
    array_[nodesCount_-1][i] = std::make_pair(0,0);
    array_[i].push_back(std::make_pair(0,0));
  }
  array_[nodesCount_ - 1][nodesCount_- 1] = std::make_pair(0,0);
  nodes_.push_back(value);
}
template <typename Node, typename Weight>
void Graph<Node,Weight>::insertBranch(const Node& first, const Node& last)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return;
  }
  size_t start = index(first);
  if (start >= nodesCount_)
  {
    throw std::out_of_range("first node doesn't exist");
    return;
  }
  size_t end = index(last);
  if (end >= nodesCount_)
  {
    throw std::out_of_range("second node doesn't exist");
    return;
  }
  if (start == end)
  {
    array_[start][end] = std::make_pair(
      std::get<0>(array_[start][end]) - 1,
      std::get<1>(array_[start][end]) + 1
    );
  }
  else
  {
    array_[start][end] = std::make_pair(
      std::get<0>(array_[start][end]),
      std::get<1>(array_[start][end]) + 1
    );
    array_[end][start] = std::make_pair(
      std::get<0>(array_[end][start]) - 1,
      std::get<1>(array_[end][start])
    );
  }
}
template <typename Node, typename Weight>
void Graph<Node,Weight>::removeNode(const Node& node)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return;
  }
  if (existsNode(node))
  {
    if (nodesCount_ == 1)
    {
      array_.clear();
      array_.shrink_to_fit();
      nodes_.clear();
      nodes_.shrink_to_fit();
      nodesCount_ = 0;
      return;
    }
    size_t iNode = index(node);
    nodesCount_--;
    for (size_t i = 0; i<=nodesCount_; i++)
    {
      if (i!=iNode)
      {
        array_[i].erase(array_[i].begin() + iNode);
        array_[i].shrink_to_fit();
      }
    }
    array_.erase(array_.begin() + iNode);
    array_.shrink_to_fit();
    nodes_.erase(nodes_.begin() + iNode);
    nodes_.shrink_to_fit();
  }
  else
  {
    throw std::invalid_argument("removing a non-existant node");
  }
}
template <typename Node,typename Weight>
void Graph<Node,Weight>::removeBranch(const Node& first, const Node& second)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return;
  }
  size_t index1 = index(first);
  size_t index2 = index(second);
  if (index1<nodesCount_ && index2<nodesCount_)
  {
    if (index1 == index2)
    {
      if (std::get<1>(array_[index1][index2])>0)
      {
        array_[index1][index2] = std::make_pair(
          std::get<0>(array_[index1][index2]) + 1,
          std::get<1>(array_[index1][index2]) - 1
        );
      }
      else
      {
        throw std::invalid_argument("branch does not exist");
      }
    }
    else if (std::get<1>(array_[index1][index2])>0)
    {
      array_[index1][index2] = std::make_pair(
        std::get<0>(array_[index1][index2]),
        std::get<1>(array_[index1][index2]) - 1
      );
      array_[index2][index1] = std::make_pair(
        std::get<0>(array_[index2][index1]) + 1,
        std::get<1>(array_[index2][index1])
      );
    }
    else
    {
      throw std::invalid_argument("branch does not exist");
    }
  }
  else
  {
    throw std::invalid_argument("nodes do not exist");
  }
}
template <typename Node,typename Weight>
void Graph<Node,Weight>::print(std::ostream& out)
{
  std::ostream::sentry ward(out);
  if (!ward)
  {
    throw std::ios_base::failure("ostream is not accessible");
    return;
  }
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
    return;
  }
  out << '\t';
  std::copy(
    std::begin(nodes_),
    std::end(nodes_),
    std::ostream_iterator<Node>(out, "\t")
  );
  out << '\n';
  for (size_t i = 0; i<nodesCount_; i++)
  {
    out << nodes_[i] << '\t';
    for (size_t j = 0; j<nodesCount_; j++)
    {
      out << std::get<0>(array_[i][j]) << ':' << std::get<1>(array_[i][j]) << '\t';
    }
    out << '\n';
  }
}
template <typename Node,typename Weight>
Weight Graph<Node,Weight>::totalDegree(const Node& node)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  size_t ind = index(node);
  if (ind>=nodesCount_)
  {
    throw std::invalid_argument("invalid node");
  }
  struct getter
  {
    Weight operator()(Weight total, std::pair<Weight,Weight> pair)
    {
      total+= std::get<1>(pair) - std::get<0>(pair);
      return total;
    }
  };
  Weight total = std::accumulate(
    array_[ind].begin(),
    array_[ind].end(),
    0,
    getter()
  );
  return total;
}
template <typename Node,typename Weight>
Weight Graph<Node,Weight>::inDegree(const Node& node)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  size_t ind = index(node);
  if (ind>=nodesCount_)
  {
    throw std::invalid_argument("invalid node");
  }
  struct getter
  {
    Weight operator()(Weight total, std::pair<Weight,Weight> pair)
    {
      total+= std::get<0>(pair);
      return total;
    }
  };
  Weight total = std::accumulate(
    array_[ind].begin(),
    array_[ind].end(),
    0,
    getter()
  );
  return -1*total;
}
template <typename Node,typename Weight>
Weight Graph<Node,Weight>::outDegree(const Node& node)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  size_t ind = index(node);
  if (ind>=nodesCount_)
  {
    throw std::invalid_argument("invalid node");
  }
  struct getter
  {
    Weight operator()(Weight total, std::pair<Weight,Weight> pair)
    {
      total+= std::get<1>(pair);
      return total;
    }
  };
  Weight total = std::accumulate(
    array_[ind].begin(),
    array_[ind].end(),
    0,
    getter()
  );
  return total;
}
template <typename Node,typename Weight>
std::pair<Node,Weight> Graph<Node,Weight>::maxDegree(short int param)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  std::pair<Node,Weight> max = std::make_pair(0, std::numeric_limits<Weight>::min());
  Weight degree = 0;
  for (size_t i = 0; i<nodesCount_; i++)
  {
    switch(param)
    {
      case(1):
        degree = outDegree(nodes_[i]);
        break;
      case(-1):
        degree = inDegree(nodes_[i]);
        break;
      case(0):
        degree = totalDegree(nodes_[i]);
        break;
      default:
        throw std::invalid_argument("invalid parameter");
        break;
    }
    if (degree>std::get<1>(max))
    {
      max = std::make_pair(
        nodes_[i],
        degree
      );
    }
  }
  return max;
}
template <typename Node,typename Weight>
void Graph<Node,Weight>::DFSR(size_t startingIndex, size_t currentIndex)
{
  if (currentIndex>=nodesCount_)
  {
    throw std::out_of_range("DFS invalid index");
    return;
  }
  for (size_t i = 0; i<nodesCount_;i++)
  {
    if (std::get<1>(array_[i][currentIndex])>0)
    {
      if (i == startingIndex)
      {
        removeBranch(nodes_[currentIndex],nodes_[i]);
        return;
      }
      else
      {
        Graph<Node,Weight>::DFSR(startingIndex,i);
      }
    }
  }
}
template <typename Node,typename Weight>
void Graph<Node,Weight>::removeCycles()
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  for (size_t i = 0; i < nodesCount_; i++)
  {
    array_[i][i] = std::make_pair(0,0);
    std::transform(
      array_[i].cbegin(),
      array_[i].cend(),
      array_[i].begin(),
      [](std::pair<Weight,Weight> pair)
      {
        std::pair<Weight,Weight> newPair;
        if (std::get<1>(pair) > 1)
        {
          pair = std::make_pair(
            std::get<0>(pair),
            1
          );
        }
        if (std::get<0>(pair) < -1)
        {
          pair = std::make_pair(
            -1,
            std::get<1>(pair)
          );
        }
        return pair;
      }
    );
  }
  for (size_t i = 0; i<nodesCount_; i++)
  {
    Graph<Node,Weight>::DFSR(i,i);
  }
}
template <typename Node,typename Weight>
void Graph<Node,Weight>::sources(std::ostream& out)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  for (size_t i = 0; i<nodesCount_; i++)
  {
    size_t flag = std::accumulate(
      array_[i].cbegin(),
      array_[i].cend(),
      0,
      [&out, this](size_t total, const std::pair<Weight,Weight>& pair)
      {
        if (std::get<0>(pair) < 0)
        {
          return ++total;
        }
        if (std::get<0>(pair) == 0 && std::get<1>(pair) == 0)
        {
          return total;
        }
        if (std::get<0>(pair) == 0 && std::get<1>(pair) > 0)
        {
          return total;
        }
        return total;
      }
    );
    if (!flag)
    {
      out << nodes_[i] << '\t';
    }
  }
  out << '\n';
}
template <typename Node,typename Weight>
void Graph<Node,Weight>::deltas(std::ostream& out)
{
  if (array_.size() == 0)
  {
    throw std::out_of_range("matrix is empty");
  }
  for (size_t i = 0; i<nodesCount_; i++)
  {
    size_t flag = std::accumulate(
      array_[i].cbegin(),
      array_[i].cend(),
      0,
      [&out, this](size_t total, const std::pair<Weight,Weight>& pair)
      {
        if (std::get<1>(pair) > 0)
        {
          return ++total;
        }
        if (std::get<0>(pair) == 0 && std::get<1>(pair) == 0)
        {
          return total;
        }
        if (std::get<0>(pair) < 0 && std::get<1>(pair) == 0)
        {
          return total;
        }
        return total;
      }
    );
    if (!flag)
    {
      out << nodes_[i] << '\t';
    }
  }
  out << '\n';
}
}
#endif
