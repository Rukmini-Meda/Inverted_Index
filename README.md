## Inverted Index Implementation
### Language Used: C++
### Dataset Used: Sports News Dataset

### Sports News Dataset
The dataset consists of 181 documents about Sports news. It contains 4706 terms.

### Tokenization
- The dataset is tokenized manually by verifying whether a character is a whitespace or a punctuation.
- It is truncated accordingly and added to the dictionary.
- The dataset it tokenized using a function called ispunct(c) which takes in a character and returns whether it's a punctuation.
- All the tokens are stored in a map which is part of the inverted index.

### Data structures Used
- I have used a map to store the terms, the document frequency and the address of the posting list.
- This map forms the dictionary.
- A map is used because it stores the terms sorted by default. This allows us to produce output in order.
- A Binary Search Tree (BST) is used to store the posting lists.
- A BST offers efficient search, insert, update and traversal functions with O(logn) complexity.

### Complexities
Time complexity - O(d*n*logd) wher d is the total number of documents and n is the total number of terms.
Space complexity - O(d*n) where d is the total number of documents and n is the total number of terms.

### Creating an inverted index
- Every document is traversed.
- All the terms are tokenized in a line.
- Every such obtained term in updated in the index.
- It is updated in the map by adding its name if does not exists, updating its frequency.
- Then, it's count is incremented or updated in the particular node for that document in the BST.
- Appropriately, the BST is wrote to a file to store in a drive.

### Conclusion
Inverted index is created using efficient data structures. The map is stored in memory and posting lists in drive.