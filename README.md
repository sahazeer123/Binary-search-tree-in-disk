# Binary-search-tree-in-disk
implemented binary search tree in disk
For some inputs my implementation dosen't work on windows operating system.Works with ubuntu

Initialising Tree:In initialising tree I will store the link to root and filled_head.Each time I will access those two pointers to traverse the list

Inserting node:First whenever I initialise the file I read the root of the BST.If out BST is empty I will go to the end of file and insert the node and update left and right child of parent node by calculating offset values.If our BST is not full I will traverse the list and update the links of parent node appropriately

Deleting a node:Basically deleting a node in BST has 3 cases
               1) node with no children
               2)node with one subtree/children
               3)node with both subtree 
1)node with no children:it is the easiest case.Go to the parent node and delete left and right links.
2)node with one children:traverse to the parent node of node being deleted and update the right or left link of parent node to deleting node's subtree.The parent node's linking part depends on the key value that is being deleted
3)node with both subtrees:traverse to the node being deleted.Update the key value of node being deleted by its inorder successor.Deleting inorder successor in the right subtree of node being deleted boils down to first two case because inorder successor doesen't have left child.Either tree with one subtree or that is a leaf node

Inorder_display:for inorder traversal of tree I have used two function.The main funcion calls wrapper function which is recursive in nature.

Preorder_display:for preorder traversal of tree I have use two function.The main function calls wrapper function which is 
recursive nature
