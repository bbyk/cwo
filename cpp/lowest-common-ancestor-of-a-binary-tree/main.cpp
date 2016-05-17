#include <iostream>
#include <deque>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};


class Solution {
private:
    struct BreadCrumb {
        TreeNode *node;
        bool first;
    };

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {

        // trivial case
        if (p == q) {
            return p;
        }

        unordered_set<TreeNode *> pq;
        pq.insert(p);
        pq.insert(q);
        deque<BreadCrumb> path, left_path;
        TreeNode *node = root;

        while (nullptr != node || path.size() > 0) {
            if (nullptr == node) {
                BreadCrumb &crumb = path.back();
                if (!crumb.first) {
                    path.pop_back();
                    continue;
                }

                crumb.first = false;

                for (auto it = pq.cbegin(); it != pq.cend(); ++it) {
                    if (*it == crumb.node) {
                        pq.erase(it);
                        if (pq.size() == 1) {
                            left_path = path;
                        } else {
                            auto lit = left_path.cbegin();
                            TreeNode *split = lit->node;
                            for (auto pit = path.cbegin(); pit != path.cend(); ++pit) {
                                if (lit == left_path.cend() || lit->node != pit->node) {
                                    return split;
                                }
                                split = lit->node;
                                ++lit;
                            }

                            return split;
                        }
                    }
                }

                node = crumb.node->right;
            } else {
                path.push_back({node, true});
                node = node->left;
            }
        }

        return root;
    }
};

int main() {
    Solution solution;
    TreeNode three(3);
    TreeNode five(5);
    TreeNode one(1);
    three.left = &five;
    three.right = &one;
    TreeNode six(6);
    TreeNode two(2);
    five.left = &six;
    five.right = &two;
    TreeNode seven(7);
    TreeNode four(4);
    two.left = &seven;
    two.right = &four;
    TreeNode zero(0);
    TreeNode eight(8);
    one.left = &zero;
    one.right = &eight;
    TreeNode nine(9);
    eight.right = &nine;
    TreeNode ten(10);
    nine.right = &ten;

    cout << "expected 3, was: " << solution.lowestCommonAncestor(&three, &three, &three)->val << endl;
    cout << "expected 3, was: " << solution.lowestCommonAncestor(&three, &five, &one)->val << endl;
    cout << "expected 5, was: " << solution.lowestCommonAncestor(&three, &five, &four)->val << endl;
    cout << "expected 6, was: " << solution.lowestCommonAncestor(&three, &six, &six)->val << endl;
    cout << "expected 3, was: " << solution.lowestCommonAncestor(&three, &four, &zero)->val << endl;
    cout << "expected 3, was: " << solution.lowestCommonAncestor(&three, &four, &eight)->val << endl;
    cout << "expected 9, was: " << solution.lowestCommonAncestor(&three, &nine, &ten)->val << endl;
    return 0;
}