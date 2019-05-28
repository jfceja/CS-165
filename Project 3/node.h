#include <vector>

class Node {
public:
	Node();

	Node(int m_id);

	Node(int m_id, std::vector<int> m_list);

	bool edge_exists(int m_id) const;

	std::vector<int>& get_children();

	std::vector<int> get_children() const;

	int get_m_id() const;

private:
	int m_id;
	std::vector<int> m_list;
};