struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int data, TreeNode* left, TreeNode* right) :
		        data(data), left(left), right(right) { }
	TreeNode(int data) : data(data) {
		left = nullptr;
		right = nullptr;
	}
};
class Tree {
	TreeNode* root = nullptr;
	Tree(int data) {
		this->root = new TreeNode(data);
	}
	Tree(std::vector<int> vec) {
		int idx = 0;
		while (!vec.empty()) {

		}
	}
};
