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
    return reinterpret_cast<size_t>(e.get());
}

void write_dot_recursive(std::ostream& out, expr e, std::unordered_set<size_t>& visited) {
    size_t id = get_id(e);
    if (visited.count(id)) return;
    visited.insert(id);

    // Node Style
    std::string shape = e->get_children().empty() ? "box" : "circle";
    out << "  node" << id << " [label=\"" << e->get_label() << "\", shape=" << shape << "];\n";

    // Edges
    auto children = e->get_children();
    for (auto& child : children) {
        out << "  node" << get_id(child) << " -> node" << id << ";\n";
        write_dot_recursive(out, child, visited);
    }
}

void export_to_dot(expr root, const std::string& filename) {
    std::ofstream out(filename);
    out << "digraph ExpressionTree {\n";
    out << "  rankdir=TB;\n"; // Top-to-Bottom layout
    
    std::unordered_set<size_t> visited;
    write_dot_recursive(out, root, visited);
    
    out << "}\n";
    out.close();
    std::cout << "Graph exported to " << filename << std::endl;
}


}