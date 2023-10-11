# zap
 Text file compression and decompression program using Huffman Coding



A. Files
1. main.cpp: This is the driver file for the Zap program
2. HuffmanCoder.cpp: This file allows the client to compress and decompress
text files using the Huffman coding algorithm.
3. HuffmanCoder.h: This file compresses and uncompresses text files
4. HuffmanTreeNode.cpp: This file contains the data used to build the Huffman
Tree
5. HuffmanTreeNode.h: This file stores nodes used by the Huffman encoder and
decoders
6. BinaryIO.cpp: This file allows the client to write and read zap files
7. BinaryIO.h: This file uses the strings assembled through encoding and
decoding to convert between text and zap files
8. unit_test.h: This file tests functions for the HuffmanTreeNode class
9. Makefile

B. Compiling and Running:
     - Compile using
            make zap
     - Run executable with
            ./zap [zap | unzap] inputFile outputFile
*Note that the program yield an error messsage if additional command line
arguments are provided or if any of the above arguments are specified
incorrectly

C. Data Structures and Algorithms
The main data structure used during the assignment was the priority queue.
Normal queues use a "first in, first out" approach in which elements can only
be inserted at the back and accessed at the front. Priority queues, however,
allow the user to assign some degree of preference to elements being stored.
The priority determines the order in which the elements are accessed. A real
world examples where this data structure is useful is for boarding planes.
Typically, families with children, veterans, and persons with disabilities get
to board the plane first. Priority must be quantified in this data structure,
and my implementation uses a minimum priority queue to do so. In constructing
a huffman tree, node frequency values are used to order nodes. Elements with
the lowest frequency are removed from the queue and connected through a parent
node containing the sum of their priority values. 

Like all data structures used in this course, the priority queue has various
advantages and disadvantage. Astated earlier, its intuitive mechanism for
managing items with allows the user to build more dynamic, realistic queues.
Elements can be accesessed efficiently in constant time. They also can be
utilized with programmers of different skills, given that implementation
can occur using a vector or a heap. A third advantages are its many
applications, which include sorting and searching algorithims in addition to
the airplane example described above. A limitation is that it can be difficult
to remove an items not towards the top of the queue. Suppose a situation
existed where on a particular day of the weak, certain people who receive
priority in boarding airplanes did not fly. We could not simply "delete" these
people from the queue, but rather would have to remove every previous member
before reaching the desired elements. 

It's worth noting that my priority queue uses an arraylist in its
implementation. This data structure has been explored extensively in previous
assignments, but I will briefly outline its characteristics in the interest of
being thorough C++ vectors are useful due to their capacity to grow and shrink.
The array does not actually change their size, but appears to do so for the
client through pointers to heap-allocated arrays. This allows client to avoid
thinking about memory allocation when interacting with this data structure.

The priority queue allowed me to construct a Huffman Tree, which uses a tree
data structure. Trees allow us to quickly find, insert, and remove elements.
They are useful in modeling hierarchical relationships where all nodes stem
from the root node and parent nodes points to children nodes. Leaf nodes
contain sentinels. In a Huffman tree, leaf nodes contain characters from a text
file and internal nodes contain the null character. All nodes contain
frequencies, which are letter counts for leaf nodes and the sum of children
node frequencies for internal nodes.
  
I will describe a few algorithms used in my implementation. Firstly, I used an
array to store character frequencies from text files. I initialized an integer
array of size 256 because there are only 256 ASCII chars. I converted each
character in a text file to its corresponding ASCII value and incremented the
integer at that position. In constructing the Huffman tree I used another
algorithm. First, I created nodes for positions in the array where the value was
not equal to 0 and pushed these nodes into the priority queue. Then, I popped
the nodes with the lowest frequencies, joined them with a parent node, and
pushed that back into the queue. I repeated this process until only one node
remained in the queue and set that equal to the root private member variable.
A final algorithm in my design occurred when decoding the binary strings. I
iterated through the binary string and Huffman tree. For values in the binary
string in which the position in the tree was a leaf, I appended its character
to a string and moved back to the root of the tree. Otherwise, I traversed to
the appropriate subtree. Finally, I checked to make sure the last character in
the binary string was at a leaf and returned a string containing the file text.
