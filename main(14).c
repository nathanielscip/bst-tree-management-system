/* COP 3502C Assignment 4
This program is written by: Nathaniel Scipio */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include "leak_detector_c.h"

    #define MAXLEN 30

    typedef struct itemNode
    {
      char name[MAXLEN];
      int count;
      struct itemNode *left, *right;
    }itemNode;

    typedef struct treeNameNode
    {
      char treeName[MAXLEN];
      struct treeNameNode *left, *right;
      itemNode *theTree;
    }treeNameNode;

    treeNameNode* createTreeNameNode(char *name) // allocates memory for tree node
    {
      treeNameNode *temp = (treeNameNode*)malloc(sizeof(treeNameNode));
      strcpy(temp->treeName, name);
      temp->left = NULL;
      temp->right = NULL;
      temp->theTree = NULL;

      return temp;
    }

    itemNode* createItemNode(char *name, int count) // allocates memory for item node
    {
      itemNode *temp = (itemNode*)malloc(sizeof(itemNode));
      strcpy(temp->name, name);
      temp->count = count;
      temp->left = NULL;
      temp->right = NULL;
      
      return temp;
    }

    treeNameNode* insertTreeName(treeNameNode* root, treeNameNode* element)
    {
      if(root==NULL)
        return element;

      else
      {
        if (strcmp(element->treeName, root->treeName) < 0) // inserts left if name is lower than element's ASCII value
        {
          if(root->left != NULL)
            root->left = insertTreeName(root->left, element);

          else
            root->left = element;
        }

        else // inserts right if name is higher than element's ASCII value
        {
          if(root->right != NULL)
            root->right = insertTreeName(root->right, element);

          else
            root->right = element;
        }

        return root;
      }

    }

    itemNode* insertItem(itemNode *item, itemNode *element) // operates the same as insertTreeName function
    {
      if(item == NULL)
        return element;

      else
      {
        if(strcmp(element->name, item->name) < 0)
        {
          if(item->left != NULL)
            item->left = insertItem(item->left, element);

          else
            item->left = element;
        }

        else
        {
          if(item->right != NULL)
            item->right = insertItem(item->right, element);

          else
            item->right = element;
        }

        return item;
      }
      
    }

    treeNameNode* buildNameTree(treeNameNode* root, int n)
    {
      char name[MAXLEN];

      for(int i = 0; i < n; i++)
      {
        scanf("%s", name);
        treeNameNode *temp = createTreeNameNode(name);
        root = insertTreeName(root, temp);
        
      }

      return root;
      

    }

    treeNameNode* searchNameNode(treeNameNode* currPtr, char *name)
    {
      treeNameNode* temp;
      
      if(currPtr != NULL) // traverses left or right until ASCII value is the same
      {
        if(strcmp(name, currPtr->treeName) == 0)
          return currPtr;
        
        if(strcmp(name, currPtr->treeName) < 0)
          temp = searchNameNode(currPtr->left, name);

        else
          temp = searchNameNode(currPtr->right, name);
      }

      else
        return NULL;

    }

    itemNode* searchItemNode(itemNode* currPtr, char *name)
    {
      itemNode *temp;

      if(currPtr != NULL)
      {
        if(strcmp(name, currPtr->name) == 0)
          return currPtr;
        
        if(strcmp(name, currPtr->name) < 0)
          temp = searchItemNode(currPtr->left, name);

        else
          temp = searchItemNode(currPtr->right, name);
      }

      else
        return NULL;
      
    }

    void addTreeItems(treeNameNode* root, int n)
    {
      char itemName[MAXLEN];
      char treeName[MAXLEN];
      int c;

      itemNode *item = NULL;
      treeNameNode *itemTree = NULL;

      for(int i = 0; i < n; i++)
      {
        scanf("%s %s %d", treeName, itemName, &c);
        itemTree = searchNameNode(root, treeName);
        item = createItemNode(itemName, c);
        itemTree->theTree = insertItem(itemTree->theTree, item);
      }

    }

    void traverseItems(itemNode *root)
    {
      if(root != NULL)
      {
        traverseItems(root->left);
        printf("%s ", root->name);
        traverseItems(root->right);
        
      }
    }

    void traverse_in_traverse(treeNameNode *root)
    {
      if(root != NULL)
      {
        traverse_in_traverse(root->left);
        printf("###%s###\n", root->treeName);
        traverseItems(root->theTree);
        printf("\n");
        traverse_in_traverse(root->right);
      }
    }

    void inorder (treeNameNode *p) {
      if (p != NULL) {
        inorder(p->left);
        printf("%s ", p->treeName);
        inorder(p->right);
      }
    }

    int countBefore(itemNode* item, char* name)
    {
      if(item != NULL)
      {
        if(strcmp(name, item->name) > 0)
        {
          return 1 + countBefore(item->left, name) + countBefore(item->right, name);

        }

        else
         return countBefore(item->left, name); // goes left if item's name is equal to or has lower ASCII value than name
      }

      return 0;

    }

    int count(itemNode* item)
    {
      if(item != NULL)
        return item->count + count(item->left) + count(item->right); //adds up item's counts by traversing left and right subtrees

      return 0;
    }

    int height(itemNode *root)
    {
      int leftHeight, rightHeight;

      if(root == NULL)
        return -1;

      leftHeight = height(root->left);
      rightHeight = height(root->right);

      if(leftHeight > rightHeight) // adds to height if one is greater than the other
        return leftHeight + 1;
      
      else
        return rightHeight + 1;
    }

    // following functions account for both itemNodes and treeNodes

    itemNode *parent(itemNode *root, itemNode *node)
    {
      if (root == NULL || root == node)
          return NULL;

      //root is direct parent of null
      if(root->left == node || root->right == node)
        return root;
      //look for node's parent in left side
      if(node != NULL){
        if(strcmp(node->name, root->name)<0)
          return parent(root->left, node);
        // look for node's parent in right side
        if(strcmp(node->name, root->name)>0)
          return parent(root->right, node);
      }
      
    }

    treeNameNode *parentTree(treeNameNode *root, treeNameNode *node)
    {
      if (root == NULL || root == node)
          return NULL;

      //root is direct parent of null
      if(root->left == node || root->right == node)
        return root;
      //look for node's parent in left side
      if(node != NULL){
        if(strcmp(node->treeName, root->treeName)<0)
          return parentTree(root->left, node);
        // look for node's parent in right side
        if(strcmp(node->treeName, root->treeName)>0)
          return parentTree(root->right, node);
      }
      
    }

    int isLeaf(itemNode *node)
    {
      if(node != NULL)
        return (node->left == NULL && node->right == NULL); // both nodes are null which implies that the node is at bottom of the tree
    }

    int isLeafTree(treeNameNode *node)
    {
      if(node != NULL)
        return (node->left == NULL && node->right == NULL);
    }

    int hasOnlyLeftChild(itemNode *node)
    {
      if(node != NULL)
        return (node->left != NULL && node->right == NULL); // only left side is not equal to null
    }

    int hasOnlyLeftChildTree(treeNameNode *node)
    {
      if(node != NULL)
        return (node->left != NULL && node->right == NULL);
    }

    int hasOnlyRightChild(itemNode *node)
    {
      if(node != NULL)
        return (node->left == NULL && node->right != NULL); //only right side not equal to null
    }

    int hasOnlyRightChildTree(treeNameNode *node)
    {
      if(node != NULL)
        return (node->left == NULL && node->right != NULL);
    }

    itemNode *minVal(itemNode *root) // moves left until smallest value is reached
    {
      //root stores minimum value
      if (root->left == NULL)
        return root;
      //left subtree of the root stores minimum value
      else
        return minVal(root->left);
    }

    treeNameNode *minValTree(treeNameNode *root)
    {
      //root stores minimum value
      if (root->left == NULL)
        return root;
      //left subtree of the root stores minimum value
      else
        return minValTree(root->left);
    }

    itemNode *delete(itemNode* root, char *itemName) // delete function for item
    {
      itemNode *delnode, *new_del_node, *save_node;
      itemNode *par;
      char save_name[MAXLEN];

      delnode = searchItemNode(root, itemName); // searches for node that is getting deleted

      par = parent(root, delnode);

      if(isLeaf(delnode))
      {
        if (par == NULL)
        {
          free(root);
          root = NULL;
          return NULL;
        }

        if(strcmp(itemName, par->name)<0)
        {
          free(par->left);
          par->left = NULL;
        }

        else
        {
          free(par->right);
          par->right = NULL;
        }

        return root;
      }

      if(hasOnlyLeftChild(delnode))
      {
        if (par == NULL)
        {
          save_node = delnode->left;
          free(delnode);
          delnode = NULL;
          return save_node;
        }

        if(strcmp(itemName, par->name)<0)
        {
          save_node = par->left;
          par->left = par->left->left;
          free(save_node);
          save_node = NULL;
        }

        else
        {
          save_node = par->right;
          par->right = par->right->left;
          free(save_node);
          save_node = NULL;
        }

        return root;

      }

      if(hasOnlyRightChild(delnode))
      {
        if (par == NULL)
        {
          save_node = delnode->left;
          free(delnode);
          delnode = NULL;
          return save_node;
        }

        if(strcmp(itemName, par->name)<0)
        {
          save_node = par->left;
          par->left = par->left->right;
          free(save_node);
          save_node = NULL;
        }

        else
        {
          save_node = par->right;
          par->right = par->right->right;
          free(save_node);
          save_node = NULL;
        }

        return root;

      }
      // when node has both children
      new_del_node = minVal(delnode->right); // gets minimum value to delete and move up 
      strcpy(save_name, new_del_node->name);

      delete(root, save_name);

      strcpy(delnode->name, save_name);

      return root;
        
    }

    void freeAllItems(itemNode* root) // recursively frees items
    {
      if(root != NULL)
      {
        freeAllItems(root->left);
        freeAllItems(root->right);
        free(root);
        root = NULL;
      }

    }

    treeNameNode *delete_name(treeNameNode* root, char *treeName) // deletes tree nodes
    {
      treeNameNode *delnode, *new_del_node, *save_node;
      treeNameNode *par;
      char save_name[MAXLEN];

      delnode = searchNameNode(root, treeName);;

      par = parentTree(root, delnode);

      if(isLeafTree(delnode))
      {
        if (par == NULL)
        {
          freeAllItems(root->theTree);
          free(root);
          return NULL;
        }

        if(strcmp(treeName, par->treeName)<0)
        {
          freeAllItems(par->left->theTree);
          free(par->left);
          par->left = NULL;
        }

        else
        {
          freeAllItems(par->right->theTree);
          free(par->right);
          par->right = NULL;
        }

        return root;
      }

      if(hasOnlyLeftChildTree(delnode))
      {
        if (par == NULL)
        {
          save_node = delnode->left;
          freeAllItems(delnode->theTree);
          free(delnode);
          return save_node;
        }

        if(strcmp(treeName, par->treeName)<0)
        {
          save_node = par->left;
          par->left = par->left->left;
          freeAllItems(save_node->theTree);
          free(save_node);
        }

        else
        {
          save_node = par->right;
          par->right = par->right->left;
          freeAllItems(save_node->theTree);
          free(save_node);
        }

        return root;

      }

      if(hasOnlyRightChildTree(delnode))
      {
        if (par == NULL)
        {
          save_node = delnode->left;
          freeAllItems(delnode->theTree);
          free(delnode);
          return save_node;
        }

        if(strcmp(treeName, par->treeName)<0)
        {
          save_node = par->left;
          par->left = par->left->right;
          freeAllItems(save_node->theTree);
          free(save_node);
        }

        else
        {
          save_node = par->right;
          par->right = par->right->right;
          freeAllItems(save_node->theTree);
          free(save_node);
        }

        return root;

      }


      new_del_node = minValTree(delnode->right);
      strcpy(save_name, new_del_node->treeName);

      delete_name(root, save_name);

      strcpy(delnode->treeName, save_name);

      return root;
    }

    void freeAllTrees(treeNameNode* root) // recursively frees trees
    {
      if(root != NULL)
      {
        
        //freeAllItems(root->theTree);
        freeAllTrees(root->left);
        freeAllTrees(root->right);
        free(root);
        root = NULL;
      }
    }


    void decrease(treeNameNode *root, char* tName, char* iName, int c)
    {
      treeNameNode* decTree = searchNameNode(root, tName);
      itemNode* decItem = searchItemNode(decTree->theTree, iName);

      decItem->count -= c; // deletes count 

      if(decItem->count <= 0) // if result is <= 0 the delete function is called to remove node
        delete(decItem, decItem->name);
      
    }


    void queries(treeNameNode *root, int n) // function takes care of all query options
    {
      char query[MAXLEN], treeName[MAXLEN], itemName[MAXLEN];
      int c;
      
      for(int i = 0; i < n; i++)
      {
        scanf("%s", query);

        if(strcmp(query, "find") == 0)
        {
          scanf("%s %s", treeName, itemName);
          treeNameNode* findTree = searchNameNode(root, treeName);
          if(findTree == NULL)
            printf("%s does not exist\n", treeName);
          else{
            itemNode* findItem = searchItemNode(findTree->theTree, itemName);
            if(findItem==NULL)
              printf("%s not found in %s\n", itemName, treeName);
            else
              printf("%d %s found in %s\n", findItem->count, findItem->name, findTree->treeName);
          }
        }

        if(strcmp(query, "count_before")==0)
        {
          scanf("%s %s", treeName, itemName);
          treeNameNode* cbTree = searchNameNode(root, treeName);
          int cbCount = 0;
          cbCount = countBefore(cbTree->theTree, itemName);
          printf("Item before %s: %d\n", itemName, cbCount);
        }

        if(strcmp(query, "count")==0)
        {
          scanf("%s", treeName);
          treeNameNode* cTree = searchNameNode(root, treeName);
          int cCount = count(cTree->theTree);
          printf("%s count %d\n", cTree->treeName, cCount);
          
        }

        if(strcmp(query, "check_balance")==0)
        {
          scanf("%s", treeName);
          treeNameNode* checkTree = searchNameNode(root, treeName);
          int lHeight = height(checkTree->theTree->left);
          int rHeight = height(checkTree->theTree->right);
          int dif = abs(rHeight - lHeight);
          
          printf("%s: left height %d, right height %d, difference %d, ", checkTree->treeName, lHeight, rHeight, dif);

          if(dif>1)
            printf("not balanced\n");
          else
            printf("balanced\n");
                  
        }

        if(strcmp(query, "decrease")==0)
        {
          scanf("%s %s %d", treeName, itemName, &c);
          decrease(root, treeName, itemName, c);
          printf("%s reduced\n", itemName);
          
        }

        if(strcmp(query, "remove")==0)
        {
          scanf("%s %s", treeName, itemName);
          treeNameNode* tree = searchNameNode(root, treeName);
          itemNode* remItem = searchItemNode(tree->theTree, itemName);
          delete(remItem, remItem->name);
          printf("%s deleted from %s\n", itemName, treeName);
        }

        if(strcmp(query, "delete_name")==0)
        {
          scanf("%s", treeName);
          treeNameNode* delTree = searchNameNode(root, treeName);
          //freeAllItems(delTree->theTree);
          delete_name(root, treeName);
          printf("%s deleted\n", treeName);
        }
      }

    }


    int main() 
    {
      atexit(report_mem_leak);
      int n, i, q;  
      treeNameNode* root = NULL;

      scanf("%d %d %d", &n, &i, &q);
      root = buildNameTree(root, n);
      addTreeItems(root, i);
      inorder(root);
      printf("\n");
      traverse_in_traverse(root);
      queries(root, q);

      freeAllTrees(root);
      
      return 0;
      
    }
