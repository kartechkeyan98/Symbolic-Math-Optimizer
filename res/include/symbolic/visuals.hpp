#pragma once

#include<symbolic/expression.hpp>
#include<symbolic/leafs.hpp>

// std libs
#include<iostream>
#include<fstream>
#include<sstream>
#include<unordered_set>

namespace symbolic{

size_t get_id(const expr &e){
    return std::hash<expr>{}(e);
}

void export_to_dot(expr root, const std::string& filename) {
    if (!root) {
        std::cerr << "Error: Null expression root" << std::endl;
        return;
    }

    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    out << "digraph ExpressionTree {\n";
    out << "  rankdir=TB;\n";

    std::unordered_set<size_t> visited;
    std::vector<expr> stack = {root};
    std::vector<std::pair<size_t, size_t>> edges; // store edges to write after nodes

    while (!stack.empty()) {
        expr current = stack.back();
        stack.pop_back();

        if (!current) continue;

        size_t id = reinterpret_cast<size_t>(current.get());
        if (visited.count(id)) continue;
        visited.insert(id);

        // Get children safely
        std::vector<expr> children;
        try {
            children = current->get_children();
        } catch (...) {
            children = std::vector<expr>();
        }

        // Write node
        std::string label;
        try {
            label = current->get_label();
        } catch (...) {
            label = "?";
        }
        std::string shape = children.empty() ? "box" : "circle";
        out << "  node" << id << " [label=\"" << label << "\", shape=" << shape << "];\n";

        // Record edges and push children
        for (auto& child : children) {
            if (child) {
                size_t child_id = reinterpret_cast<size_t>(child.get());
                edges.emplace_back(child_id, id);
                stack.push_back(child);
            }
        }
    }

    // Write all edges
    for (auto& edge : edges) {
        out << "  node" << edge.first << " -> node" << edge.second << ";\n";
    }

    out << "}\n";
    out.flush();
    out.close();
    std::cout << "Exported to " << filename << std::endl;
}


}