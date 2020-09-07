/**
 *    Implementation of Inverted Index for 181 documents.
 * -----------------------------------------------------------
 * Every document is parsed into terms and index is made on the terms such that retrieval becomes efficient.
*/

//Required header files
#include<bits/stdc++.h>
#include<fstream>
#include<sstream>
#include<dirent.h>
using namespace std;

// Class definition for a node in a bst
class Node{
public:
    //Document ID, frequency in that doc
    int doc_num;
    int freq;
    Node *left,*right;
    //Constructor
    Node(int doc){
        this->doc_num = doc;
        this->freq = 1;
        this->left = NULL;
        this->right = NULL;
    }
};

//Class definition for a BST
class BST{
public:
    //Root of the BST
    Node *root;
    //Constructor
    BST(){
        this->root = NULL;
    }
    //Utility function to search for a document in the BST
    bool search(Node *root,int id){
        if(root != NULL){
            if(root->doc_num == id){
                return true;    //Document found
            }
            else if(root->doc_num<id){
                bool val1 = search(root->right,id);
                if(val1 == true){
                    return true;
                }
            }
            else{
                bool val1 = search(root->left,id);
                if(val1 == true){
                    return true;
                }
            }
        }
        return false;    //Document not found
    }

    //Utility function to insert a new document in the BST
    Node* insert_doc(Node *root,int id){
        if(root == NULL){
            return new Node(id);     //Creating a new node and returning for insertion
        }
        if(root->doc_num<id){
            root->right = insert_doc(root->right,id);
        }
        else{
            root->left = insert_doc(root->left,id);
        }
        return root;
    }

    //Utility function to update a new document in the BST.
    void update_doc(Node *root,int id){
        if(root->doc_num == id){
            root->freq++;        //Frequency of that doc incremented.
            return;
        }
        else if(root->doc_num<id){
            update_doc(root->right,id);
        }
        else{
            update_doc(root->left,id);
        }  
    }

    //Utility function for inorder traversal of the BST
    void inorderTraversal(Node *node,string& str2){
        if(node != NULL){
            if(str2 != ""){
                str2 += ", ";
            }
            str2 += to_string(node->doc_num);
            str2 += "=";
            str2 += to_string(node->freq);
            inorderTraversal(node->left,str2);
            inorderTraversal(node->right,str2);
        }
    }
};

class InvertedIndex{
    public:
    //Inverted index structure
    map< string,pair<int,BST*> > dictionary;

    //Utility function to update index for any term found.
    void update_index(string word,int doc){
        bool flag = true;
        if(this->dictionary.find(word)==this->dictionary.end()){
            this->dictionary[word].first = 1;
            this->dictionary[word].second = new BST();
            flag = false;
        }
        BST *tree = (this->dictionary[word].second);
        bool val = (*tree).search(tree->root,doc);
        if(val == true){
            (*tree).update_doc(tree->root,doc);    //Updating doc
        }
        else{
            tree->root = (*tree).insert_doc(tree->root,doc);  //Inserting doc
            if(flag == true){
                this->dictionary[word].first++;
            }
        }
    }
    //Utility function to write the index to file.
    void writeIndex(){
        map<string, pair<int,BST*> >::iterator it;
        fstream file,file1;
        string str ="";
        file.open("output.txt",ios::out);                   //Opening the file
        for(it=this->dictionary.begin();it!=this->dictionary.end();it++){
            file << it->first << " (" << (it->second).first << ") ==> {";
            string str="";
            BST *tree = (it->second).second;
            tree->inorderTraversal(tree->root,str);
            file << str << "}" << endl;
        }
        file.close();                     //Closing the file
    }

};
//Driver function of the program
int main(){
    clock_t start, end;
    start = clock();
    //Opening the directory for the dataset
    DIR *dir;
    dirent *pdir;
    string files[200];
    dir = opendir("th-dataset");
    int i=0;
    while((pdir=readdir(dir))!=NULL){
        files[i] = "th-dataset/";
        files[i] += pdir->d_name;
        i++;
    }
    int total = i;
    closedir(dir);
    InvertedIndex index;
    //Looping over all documents to create inverted index
    for(int i=2;i<total;i++){
        fstream file;
        int doc_number = 99 + i;  //Generalizing the doc ID.
        file.open(files[i],ios::in);
        if(!file){
            cout << "File not found!!" << endl;     //Warning
        }
        else{
            string str;
            int line = 1;
            while(getline(file,str)){
                int len = str.size();
                string word = "";
                for(int i=0;i<len;i++){
                    if(str[i] == ' '||str[i]=='\t'||str[i]=='\n'|| ispunct(str[i]) || str[i]<0 || str[i]>128){
                        if(word != ""){
                            index.update_index(word,doc_number);    //Updating the index for the term found
                            word = "";
                        }
                    }
                    else{
                        word+=str[i];
                    }
                }
            }
        }
        file.close();
    }
    index.writeIndex();      //Outputting the index to file
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 
    cout << "Total number of terms are " << index.dictionary.size() << endl;
    return 0;
}