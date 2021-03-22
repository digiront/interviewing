#include <string>
#include <memory>
#include <vector>
#include <optional>
#include <cassert>
#include <map>
#include <functional>

enum class NodeType {
    UNKNOWN = 0,
    FILE = 1,
    DIRECTORY = 2
};

struct Util {
    static std::vector<std::string> SplitString(const std::string &str, const std::string &delimiter = "/") {
        std::vector<std::string> components;
        size_t last = 0;
        size_t next = 0;
        while ((next = str.find(delimiter, last)) != std::string::npos) {
            components.push_back(str.substr(last, next - last));
            last = next + delimiter.size();
        }
        components.push_back(str.substr(last));
        return components;
    }
};

struct Node {
    std::string basename;
    std::string full_path;
    NodeType node_type = NodeType::UNKNOWN;
    std::optional<std::string> content; // todo
    Node *parent = nullptr;
    std::map<std::string, std::unique_ptr<Node>> children;

    [[nodiscard]] Node *FindChildWithBasename(const std::string &basename) const {
        auto it = children.find(basename);
        if (it == children.end()) return nullptr;
        return it->second.get();
    }
};

class FileSystem {
public:
    bool Mkdir(const std::string &path) {
        return InsertNode(path, NodeType::DIRECTORY);
    }

    bool InsertNode(const std::string &full_path, NodeType node_type) {
        if (full_path.empty()) return false;

        const auto components = Util::SplitString(full_path);
        return CreateNode(components, node_type);
    }

    bool DeleteNode(const std::string &full_path) {
        Node *node = FindMutableNode(full_path);
        if (node != nullptr) {
            Node *parent = node->parent;
            parent->children.erase(node->basename);
            return true;
        }
        return false;
    }

    void VisitAll(const std::string &starting_path, const std::function<void(const Node &)> &visitor_callback) const {
        const Node *node = FindNode(starting_path);
        VisitAll(node, visitor_callback);
    }

    bool NodeExists(const std::string &path) {
        return FindNode(path) != nullptr;
    }

    bool FileExists(const std::string &path) {
        const Node *node = FindNode(path);
        return node != nullptr && node->node_type == NodeType::FILE;
    }

    bool DirExists(const std::string &path) {
        const Node *node = FindNode(path);
        return node != nullptr && node->node_type == NodeType::DIRECTORY;
    }

    size_t NumNodes() const {
        return num_nodes;
    }

private:
    bool CreateNode(const std::vector<std::string>& components, NodeType node_type) {
        if (components.empty()) return false;

        std::string current_path;
        Node* current_node = &root;
        for (size_t i = 0; i < components.size(); ++i) {
            const auto& c = components[i];
            current_path += current_node->basename;
            if (current_node->children.count(c)) {
                current_node = current_node->children[c].get();
            }
            else if (i == components.size() - 1){
                auto new_node = std::make_unique<Node>();
                new_node->full_path = current_path;
                new_node->basename = c;
                new_node->node_type = node_type;
                Node *new_node_ptr = new_node.get();
                new_node->parent = current_node;
                current_node->children[c] = std::move(new_node);
                return true;
            }
        }
        return false;
    }

    // This is the most useful function
    [[nodiscard]] const Node *FindNode(const std::string &path) const {
        if (path.empty() || path == "/") {
            return &root;
        }

        const Node *node = &root;
        const auto components = Util::SplitString(path);
        for (const auto &component : components) {
            node = node->FindChildWithBasename(component);
            if (node == nullptr) return nullptr;
        }
        return node;
    }

    [[nodiscard]] Node *FindMutableNode(const std::string &path) const {
        return const_cast<Node *>(FindNode(path));
    }

    static void VisitAll(const Node *current_node, const std::function<void(const Node &)> &visitor_callback) {
        if (current_node == nullptr) return;
        for (const auto&[name, c] : current_node->children) {
            visitor_callback(*c);
            VisitAll(c.get(), visitor_callback);
        }
    }

    Node root;
    size_t num_nodes = 0;
    Node *cwd = nullptr;
};

void AddNodes(FileSystem &fs) {
    assert(fs.InsertNode("a", NodeType::DIRECTORY));
    assert(fs.InsertNode("b", NodeType::DIRECTORY));
    assert(fs.InsertNode("c", NodeType::DIRECTORY));
    assert(fs.InsertNode("a/a", NodeType::DIRECTORY));
    assert(fs.InsertNode("a/a/a.txt", NodeType::FILE));
    assert(fs.InsertNode("a/b", NodeType::DIRECTORY));
    assert(fs.InsertNode("a/c", NodeType::DIRECTORY));
}

void TestInsertion() {
    FileSystem fs;
    AddNodes(fs);
    assert(fs.InsertNode("a/c", NodeType::DIRECTORY) == false);
    assert(fs.InsertNode("a/a/a.txt", NodeType::FILE) == false);
}

void TestTraversal() {
    FileSystem fs;
    AddNodes(fs);

    std::vector<std::string> visited_nodenames;
    fs.VisitAll("", [&visited_nodenames](const Node &node) {
        visited_nodenames.push_back(node.full_path);
    });
    assert(visited_nodenames.size() == 7);

    visited_nodenames.clear();
    fs.VisitAll("a/a", [&visited_nodenames](const Node &node) {
        visited_nodenames.push_back(node.full_path);
    });
    assert(visited_nodenames.size() == 1);
}

void TestDelete() {
    FileSystem fs;
    AddNodes(fs);
    assert(fs.DeleteNode("a/a"));
    assert(fs.NodeExists("a/a") == false);
    assert(fs.NodeExists("a/a/a.txt") == false);
    assert(fs.InsertNode("a/a", NodeType::DIRECTORY));
}

int main() {
    TestInsertion();
    TestTraversal();
    TestDelete();
    return 0;
}

