class Priority_queue_base {
public:
    virtual ~Priority_queue_base() { }
    virtual bool empty() const = 0;
    virtual void insert(int x) = 0;
    virtual int pop_min() = 0;
    virtual void pq_sort() = 0;
}; // class Priority_queue_base

class PQ_heap : public Priority_queue_base{
private:
    vector<int> vec;
    unsigned long long int count = 0;
public:
  //The starting index of the queue will be vec[1]
  PQ_heap()
  {
    vec.push_back(0);
  }
  ~PQ_heap()
  {}
  // int &operator[](int i)
  // {
  //   return vec.at(i);
  // }
  //Subtracting the size by 1 since the first element is not counted for
  int size()
  {
    return vec.size() - 1;
  }
  bool empty() const
  {
    if (vec.size() - 1 == 0) {
      return true;
    }
    return false;
  }
  int left(int leftchild)
  {
    if (leftchild < 0)
    {
      cmpt::error("left child must be >= 0");
    }
    count++;
    return 2*leftchild;
  }
  int right(int rightchild)
  {
    if (rightchild < 0)
    {
      cmpt::error("right child must be >= 0");
    }
    count++;
    return 2*rightchild+1;
  }
  int parent(int parentnode)
  {
    if (parentnode <= 0)
    {
      cmpt::error("parent node must be > 0");
    }
    count++;
    return parentnode/2;
  }
  void insert(int x)
  {
    //Push new node to the end
    vec.push_back(x);
    int queuesize = size();
    //Move the new node to its level
    while (queuesize != 0 && (vec[queuesize] < vec[parent(queuesize)]))
    {
      count++;
      swap(vec[queuesize],vec[parent(queuesize)]);
      queuesize = parent(queuesize);
    }
  }
  int pop_min()
  {
    //Return on empty queue
    if (empty())
    {
      cmpt::error("empty queue");
    }
    //Get the front value
    int popped = vec[1];
    //Replace the front value with the end value
    vec[1] = vec.back();
    //Erase the value at the end
    vec.pop_back();
    //Finding the smallest element in the tree to be the root (1st element of list)
    int queuesize = size();
    //Start at the swapped first value of tree (root)
    int currentlocation = 1;
    while (true)
    {
      //Get the value of the left and right child of the current node
      int leftchild = left(currentlocation);
      int rightchild = right(currentlocation);
      //Access the value of the current node
      int& currentnode = vec[currentlocation];
      //Increment each time an comparison is made
      //Break from loop if the position of the left child and the position of the right
      //child exceeded the total size of the queue (i.e the max heigh of the tree)
      if (leftchild > queuesize && rightchild > queuesize)
      {
        count++;
        break;
      }
      //If the currentnode is smaller than it's left child
      else if (currentnode > vec[leftchild])
      {
        count = count + 2;
        //Check if the leftchild is bigger than the right child
        //if so, swap the value of the current node and its right child
        //else, swap with left child
        if (vec[leftchild] > vec[rightchild])
        {
          count++;
          swap(currentnode, vec[rightchild]);
          currentlocation = rightchild;
        }
        else
        {
          swap(currentnode, vec[leftchild]);
          currentlocation = leftchild;
        }
      }
      //If the currentnode is smaller than it's right child
      else if (currentnode > vec[rightchild])
      {
        count = count + 3;
        //Check if the right child is bigger than the left child
        //if so, swap the value of the current node and its left child
        //else, swap with right child
        if (vec[rightchild] > vec[leftchild])
        {
          count++;
          swap(currentnode, vec[leftchild]);
          currentlocation = leftchild;
        }
        else
        {
          swap(currentnode, vec[rightchild]);
          currentlocation = rightchild;
        }
      }
      //Break if all cases fails
      else
      {
        break;
      }
    }
    return popped;
  }
  void pq_sort()
  {
    PQ_heap pq;
    for (auto iterate = vec.begin(); iterate != vec.end(); iterate++)
    {
      pq.insert(*iterate);
    }
    vec.clear();
    while (!pq.empty())
    {
      vec.push_back(pq.pop_min());
    }
    count = count + pq.count;
  }
  void print() const
  {
    for (auto iterate = vec.begin(); iterate != vec.end(); iterate++)
    {
      cout << *iterate << " ";
    }
    cout << endl;
  }
  int comparecount()
  {
    return count;
  }
};