import unittest
from bbyk.treeTraversal import TraversalUtils
from bbyk.treeTraversal import Node

class TraversalUtilsTests(unittest.TestCase):
    def setUp(self):
        self.root = Node(100)
        self.root.left = Node(50)
        self.root.right = Node(150)
        self.root.left.right = Node(75)

    def test_preorder(self):
        self.assertEqual([100, 50, 75, 150], [node.val for node in TraversalUtils.visit_preorder(self.root)])

    def test_inorder(self):
        self.assertEqual([50, 75, 100, 150], [node.val for node in TraversalUtils.visit_inorder(self.root)])

    def test_postorder(self):
        self.assertEqual([75, 50, 150, 100], [node.val for node in TraversalUtils.visit_postorder(self.root)])
        # \ tree
        tree = Node(100)
        tree.right = Node(150)
        tree.right.right = Node(200)

        self.assertEqual([200, 150, 100], [node.val for node in TraversalUtils.visit_postorder(tree)])

        # / tree
        tree = Node(100)
        tree.left = Node(75)
        tree.left.left = Node(50)

        self.assertEqual([50, 75, 100], [node.val for node in TraversalUtils.visit_postorder(tree)])

        # 1 node tree
        tree = Node(100)

        self.assertEqual([100], [node.val for node in TraversalUtils.visit_postorder(tree)])

        # s tree
        tree = Node(100)
        tree.left = Node(75)
        tree.left.right = Node(85)
        tree.left.right.left = Node(80)

        self.assertEqual([80, 85, 75, 100], [node.val for node in TraversalUtils.visit_postorder(tree)])

    def test_max_height(self):
        oneNode = Node(1)
        self.assertEqual(2, TraversalUtils.max_height(self.root))
        self.assertEqual(0, TraversalUtils.max_height(oneNode))

if __name__ == '__main__':
    unittest.main()