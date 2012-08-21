__author__ = 'bbyk'

class TraversalUtils(object):
    """
    Finds maximum height (depth) of the binary tree. Similar to a preorder or inorder algorithm.
    Maintain current level variable. Every time we dive increment current. Every time we pop, use
    size of stack as current.
    """

    @staticmethod
    def max_height(node):
        max_height = 0
        current = -1
        stack = []
        while True:
            if node is None:
                if not len(stack): break
                node = stack.pop()
                node = node.right
                current = len(stack)
            else:
                current += 1
                stack.append(node)
                node = node.left
            max_height = max(current, max_height)

        return max_height

    @staticmethod
    def visit_preorder(node):
        """
        Visit node, node.left, node.right

        Basic idea is to visit current node and keep it in stack
        when moving left. If current Node is None, pop parent and
        go right.
        """
        stack = []
        while True:
            if node is None:
                if not len(stack): break
                node = stack.pop()
                node = node.right
            else:
                yield node # visit node
                stack.append(node) # spare the node
                node = node.left # go visit left    @staticmethod

    @staticmethod
    def visit_inorder(node):
        """
        Visit node.left, node, node.right

        Basic idea is to keep current node in stack
        when moving left. If current Node is None, pop parent, visit it and
        go right.
        """
        stack = []
        while True:
            if node is None:
                if not len(stack): break
                node = stack.pop()
                yield node # visit node; either node or node.left
                node = node.right
            else:
                stack.append(node) #spare the node
                node = node.left # go visit left

    @staticmethod
    def visit_postorder(node):
        """
        Visit node.left, node.right, node

        More complicated algorithm of all. There are two case when we can
        yield a node.
        1. node is terminating
        2. when node is None, examine if stack is empty or pop the node from stack and check if last node is a child
        the node. If so, visit the node.
        """
        stack = []
        last = node

        while True:
            if node is None:
                if not len(stack): # stack is empty
                    break
                node = stack.pop()

                # condition to yield: stack is empty or last is a child of node
                if not len(stack) or node.right == last or node.left == last:
                    last = node
                    yield node # visit the node
                    node = None
            else:
                if node.left is None and node.right is None:
                    last = node
                    yield node # visit the node
                    node = None
                    continue

                # put node and its right child on the stack
                stack.append(node)
                if not node.right is None:
                    stack.append(node.right)

                last = node
                node = node.left

