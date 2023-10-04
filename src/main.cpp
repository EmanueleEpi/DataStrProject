#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Node
{
    public:
        string Name;
        int ID = 0;
        int balanceFactor;
        Node* left = NULL;
        Node* right = NULL;
};

class tree 
{
    public: 

    class Node *root;
    tree()
    {
        this->root= NULL;
    }

    Node* insertNAMEID(Node* root, string Name, int ID);
    Node* removeID(Node* root, int ID);
    bool searchID(Node* root, int ID); 
    bool searchName(Node* root, string name);
    void inOrderTraversal(Node* root, vector<Node*> &traverseList);
    void printInorder(Node* root);
    void preOrderTraversal(Node* root, vector<Node*> &TraverseList); 
    void printPreorder(Node* root);
    void postOrderTraversal(Node* root, vector<Node*> &TraverseList); 
    void printPostorder(Node* root); 
    void printLevelCount(Node* root); 
    void removeInorder(Node* root, int n); 
        
};


int height(Node* root) 
{
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + std::max(leftHeight, rightHeight);
}


// Used code from Balanced Trees slide 14

Node* rotateLeft(Node *node)
{
    Node* grandChild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandChild;



    return newParent;
}


//  Reverse of code from Balanced Trees slide 14

Node* rotateRight(Node *node)
{
    Node* grandChild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandChild;

    return newParent;
}


Node* rotateLeftRight(Node *node)
{
	Node* newChild = node->left->right;
    Node* grandChild = node->left;
    Node* greatGrandChild = node->left->right->left;

    node->left = newChild;
    newChild->left = grandChild;
    grandChild->right = greatGrandChild;
    Node* newParent = rotateRight(node);
	
    return newParent;
}


Node* rotateRightLeft(Node *node)
{
	Node* newChild = node->right->left;
    Node* grandChild = node->right;
    Node* greatGrandChild = node->right->left->right;

    node->right = newChild;
    newChild->right = grandChild;
    grandChild->left = greatGrandChild;
    Node* newParent = rotateLeft(node);

    return newParent;
}


int getBalanceFactor(Node* root) 
{
    if (root == NULL)
        return 0;
    else
        return height(root->left) - height(root->right);

}


// uses similar logic to slide 34 of Balanced trees powerpoint
Node* tree::insertNAMEID(Node* root, string Name, int ID) 
{
    // once there is a Null root, create a new node to take its place
	// this node will hold the Name and ID of the student
	if (root == NULL) 
	{
        Node* node = new Node();
        node->Name = Name;
        node->ID = ID;

		cout << "successful" << endl;
        return node;
    }

    if (root->ID > ID)
        root->left = insertNAMEID(root->left, Name, ID);

    else if (root->ID < ID)
        root->right = insertNAMEID(root->right, Name, ID);

    else 
	{
        cout << "unsuccessful" << endl;
        return root;
    }

    // check balance factor
	// use similar logic as table in slide 16 of Discussion 5 powerpoint
    root->balanceFactor = getBalanceFactor(root);

   // Left left case, do a Right rotation
    if (root->balanceFactor > 1 && ID < root->left->ID)
        return rotateRight(root);

    // Left Right case, do a Left Right rotation
    else if (root->balanceFactor > 1 && ID > root->left->ID)
        return rotateLeftRight(root);

    // Right Right case, do a Left rotation
    else if (root->balanceFactor < -1 && ID > root->right->ID)
        return rotateLeft(root);

    // Right Left case, do a Right Left rotation
    else if (root->balanceFactor < -1 && ID < root->right->ID)
        return rotateRightLeft(root);


    return root;
}


// used logic from pseudocode from slide 38 of Trees powerpoint
Node* tree::removeID(Node* root, int ID)
{
    Node* parent = root;
	Node* child = root;
    Node* newRootParent;

    string side;

	// root is empty
    if (root == NULL) 
	{
        cout << "unsuccessful" << endl;
        return root;
    }

    while (true) 
	{
		// go into if statement once the node with the matching ID has been located
        if (ID == child->ID) 
		{
            // check when node has no children
            if (child->left == NULL && child->right == NULL) 
			{
                if (side == "right")
                    parent->right = NULL;
                else if (child == root)
                    root = NULL;
                else
                    parent->left = NULL;
            }
			// when there is one right child, change the pointers accordingly
            else if (child->left == NULL && child->right != NULL) 
			{
                if (side == "right")
                    parent->right = child->right;
                else if (child == root)
                    root = child->right;
                else
                    parent->left = child->right;
            }
            // when there is one left child, change the pointers accordingly
            else if (child->left != NULL && child->right == NULL) 
			{
                if (side == "right")
                    parent->right = child->left;
                else if (child == root)
                    child->right = root->right;
                else
                    parent->left = child->left;
            }
        
            // the else loop is when the item has two children
            else 
			{
                // if the child has no right child it is the inorder predecessor
				// set the parent of the local root to reference the left child
                if (child->left->right == NULL) 
				{
                    if (child == root) 
					{
                        child->left->right = parent->right;
                        root = child->left;
                    }
                    else
                        parent->left = child->left;
                }
                // find rightmost node of left subtree
                else 
				{
                    Node* newRoot = child->left;

                    while (true) 
					{
                        if (newRoot->right == NULL) 
						{
                            if (newRoot->ID < parent->ID)
                                parent->left = newRoot;
                            else
                                parent->right = newRoot;

                            newRootParent->right = NULL;
                            newRoot->left = child->left;
                            newRoot->right = child->right;
                            break;
                        }
                        else
                            newRootParent = newRoot;
                            newRoot = newRoot->right;
                    }
                }
            }
            cout << "successful" << endl;
            return root;
        }
		// check if the node is less than the current child
		// if yes, set parent to child and child to child->left.
		// change side to "left"
        else if (ID < child->ID && child->left != NULL) 
		{
            parent = child;
            child = child->left;

			side = "left";
        }
		// check if the node is greater than the child node
		// if so, move right and set parent to child
		// set child equal to child->right
        else if (ID > child->ID && child->right != NULL) 
		{
            parent = child;
            child = child->right;

			side = "right";
        }
		// if student does not exist, unsucessful
        else if (ID != child-> ID) 
		{
            cout << "unsuccessful" << endl;
            return root;
        }
    }
}

bool tree::searchID(Node* root, int ID) 
{
    // if the root is NULL, return unsucessful
    if (root == NULL) 
	{
        cout << "unsuccessful" << endl;
        return false;
    }
	// Once the ID is found, print the name of the student
    else if (root->ID == ID) 
	{
        cout << root->Name << endl;
        return true;
    }
	// if the ID is greater than the current root, recursively move to root->right
    else if (ID > root->ID) 
	{
        searchID(root->right, ID);
    }
	// if the ID is less than the current root, recursively move to root-> eft
    else if (ID < root->ID) 
	{
        searchID(root->left, ID);
    }
	// If item is not found, return false
    return false;
}

bool tree::searchName(Node* root, string name) 
{
	// if there is no root, return unsuccessful
    if (root == NULL) 
	{
        cout << "unsuccessful" << endl;
        return false;
    }
	// Once the name is found print the ID and return true
    if (root->Name == name) 
	{
        cout << root->ID << endl;
        return true;
    }
	// keep looking for the name, traversing the loop up to n(amount of nodes) times
    searchName(root->left, name);
	searchName(root->right, name);
    
    return false;
}

// used pseudocode from slide 50 of tree powerpoint
// left, root, right
void tree::inOrderTraversal(Node* root, vector<Node*> &traverseList) 
{
	// if tree is empty return
    if (root == nullptr) 
	{
        return;
    }
	// inorder traverse the left subtree
    inOrderTraversal(root->left, traverseList);
	// add root to vector
    traverseList.push_back(root);
	// in order tranverse the right subtree
    inOrderTraversal(root->right, traverseList);
}


void tree::printInorder(Node* root) 
{
	// vector will be passed into InOrderTraversal and will be return with roots in this order
    vector<Node*> traverseList;
    inOrderTraversal(root, traverseList);

    for (int i = 0; i < traverseList.size(); i++) 
	{
        if (i == traverseList.size() - 1)
            cout << traverseList[i]->Name;
        else
            cout << traverseList[i]->Name << ", ";
    }

}

// root, left, right
void tree::preOrderTraversal(Node* root, vector<Node*> &TraverseList) 
{
    if (root == nullptr) 
	{
        return;
    }
	// add root to vector
    TraverseList.push_back(root);
	// pre order traverse the left subtree
    preOrderTraversal(root->left, TraverseList);
	// pre order traverse the right subtree
    preOrderTraversal(root->right, TraverseList);
}


void tree::printPreorder(Node* root) 
{
	// pass vector into pre order traversal to collect values in that order
    vector<Node*> TraverseList;
    preOrderTraversal(root, TraverseList);
	// print the preorder traversal
    for (int i = 0; i < TraverseList.size(); i++) 
	{
        if (i == TraverseList.size() - 1)
            cout << TraverseList[i]->Name;
        else
            cout << TraverseList[i]->Name << ", ";
    }
}

// based on pseudocode from slide 55 of trees  powerpoint
// left, right, root
void tree::postOrderTraversal(Node* root, vector<Node*> &TraverseList) 
{
    if (root == nullptr) 
	{
        return;
    }
	// post order traverse left subtree
    postOrderTraversal(root->left, TraverseList);
	// post order traverse right subtree
    postOrderTraversal(root->right, TraverseList);
	// push root into list
    TraverseList.push_back(root);
}


void tree::printPostorder(Node* root) 
{
	// initialize vector that will hold items in post order
    vector<Node*> TraverseList;
    postOrderTraversal(root, TraverseList);
	// print items in post order
    for (int i = 0; i < TraverseList.size(); i++) 
	{
        if (i == TraverseList.size() - 1)
            cout << TraverseList[i]->Name;
        else
            cout << TraverseList[i]->Name << ", ";
    }
}


void tree::printLevelCount(Node* root) 
{

    // print height of root
	// the height of the root is the same as the amount of levels
    int level = height(root);
    cout << level << endl;

}


void tree::removeInorder(Node* root, int n) 
{
    vector<Node*> TraverseList;
	// perform an inorder traversal and return a vector holding items in this order
    inOrderTraversal(root, TraverseList);
	// remove the item that holds the given ID
    removeID(root, TraverseList[n]->ID);

}

// check if string contains digits
bool checkName (string Name) 
{
    return Name.find_first_of("0123456789") == std::string::npos;
}


bool checkID(int ID) 
{
	// make sure the ID is valid
    return double(ID / 10000000) < 10 && double(ID / 10000000) > 0;
}


int main() 
{
    int NumOfCommands;
    cin >> NumOfCommands;

    int ID;
    string name;
    string line;

    Node* root = nullptr;
    tree tree;

    // used concept from programming 2 assignment
    for (int i = 0; i < NumOfCommands + 1; i++) 
	{
        // extract command by stopping at a ' '
        getline(cin, line);
        int indicator = line.find_first_of(' ');
        string command = line.substr(0, indicator);
        line = line.substr(indicator + 1);

        // insert Name and ID
        if (command == "insert") 
		{
            // extract name and ID 
            // check that name and ID are valid
            line = line.substr(1);
            indicator = line.find_first_of('\"');
            name = line.substr(0, indicator);
            ID = stoi(line.substr(indicator + 1));
            if (checkID(ID) && checkName(name)) 
			{
                auto newRoot = tree.insertNAMEID(root, name, ID);
                root = newRoot;
            }
            else
                cout << "unsuccessful";
        }
        // Remove ID
        else if (command == "remove") 
		{
            ID = stoi(line);
            root = tree.removeID(root, ID);
        }
        // Search for ID or name depending of format of input
        else if (command == "search") 
		{
            if (line[0] == '"') 
			{
                name = line.substr(1, line.length() - 2);
                tree.searchName(root, name);
            }
            else 
			{
                ID = stoi(line);
                tree.searchID(root, ID);
            }
        }
        // Inorder traversal
        else if (command == "printInorder") 
		{
            tree.printInorder(root);
            cout << endl;
        }
        // Preorder traversal
        else if (command == "printPreorder") 
		{
            tree.printPreorder(root);
            cout << endl;

        }
        // Postorder traversal
        else if (command == "printPostorder") 
		{
            tree.printPostorder(root);
            cout << endl;
        }
        // print the level count of tree
        else if (command == "printLevelCount")
            tree.printLevelCount(root);

        // remove a node from the tree in Inorder form
        else if (command == "removeInorder") 
		{
            int n = stoi(line);
            tree.removeInorder(root, n);
        }
    }
    return 0;
}

