#!/usr/bin/env python2


class MinimaxNode:

    def __init__(self, value, parent=None, child=None, next_sibling=None):
        if parent is not None and not isinstance(parent, MinimaxNode):
            raise TypeError("Parent must be a MinimaxNode or None")
        if child is not None and not isinstance(child, MinimaxNode):
            raise TypeError("Child must be a MinimaxNode or None")
        if next_sibling is not None and not isinstance(next_sibling,
                                                       MinimaxNode):
            raise TypeError("Sibling must be a MinimaxNode or None")
        self._value = int(value)
        self.parent = parent
        self.children = child
        self.next_sibling = next_sibling

    def __str__(self):
        return ("Node is child of [%s] and has value of %d"
                % (self.parent, self._value))

    def get_heuristic(self):
        return self._value


def minimax(root, depth, _is_max=True):
    if root is not None and not isinstance(root, MinimaxNode):
        raise TypeError("Root is not a MinimaxNode")
    if type(depth) is not int:
        raise TypeError("Depth is not an int")
    if root.children is None or depth <= 0:
        return root.get_heuristic()
    alpha = -1000 if _is_max else 1000
    current = root.children
    while (current is not None):
        if _is_max:
            alpha = max(alpha, minimax(current, depth - 1, not _is_max))
        else:
            alpha = min(alpha, minimax(current, depth - 1, not _is_max))
        current = current.next_sibling
    return alpha


def read_xml_tree(filename):
    from libxml2 import parseFile
    doc = parseFile(filename)
    root = doc.children
    ret = read_xml_node(root)
    doc.freeDoc()
    return ret


def read_xml_node(node):
    if node is None:
        return None
    if node.name != "Node":
        return read_xml_node(node.next)
    new_node = MinimaxNode(node.prop("value"))
    if node.children is None:
        return new_node
    c_xml_node = node.children
    c_node = p_node = None
    while (c_xml_node):
        if c_xml_node.name == "Node":
            c_node = read_xml_node(c_xml_node)
            if p_node:
            # There is a left side sibbling
                p_node.next_sibling = c_node
            else:
            # This is the first child
                new_node.children = c_node
            p_node = c_node
        c_xml_node = c_xml_node.next
    return new_node


def main():
    root = read_xml_tree("tree.xml")
#    print minimax(root, 0)
#    print minimax(root, 1)
#    print minimax(root, 2)
    print minimax(root, 3)

if __name__ == "__main__":
    main()
