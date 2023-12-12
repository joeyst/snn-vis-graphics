
class NavNode {
  private:
    std::vector<int> center;
    std::vector<int> r_xyz;
    std::vector<NavNode*> next_nodes
}

class NavGraph {
  private:
    std::vector<NavNode*>;
    NavNode* current_node;
}
