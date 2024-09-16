/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <cmath>
using namespace std;
#include <stack>

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
    * @todo Implement this function!
    */
    if(first[curDim] == second[curDim])
    {
      return (first < second);
    }
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
    * @todo Implement this function!
    */
    double currentBestDistance = 0;
    double potentialDistance = 0;
    for(int i = 0; i < Dim; i++)
    {
      double currentBestDifference = currentBest[i] - target[i];
      double potentialDifference = potential[i] - target[i];
      currentBestDistance += pow(currentBestDifference, 2);
      potentialDistance += pow(potentialDifference, 2);
    }
    if (potentialDistance == currentBestDistance)
    {
    return (potential < currentBest);
    }
    return (potentialDistance < currentBestDistance);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if (newPoints.empty()) 
     {
        root = nullptr;
    } 
    else 
    {
        vector<Point<Dim>> points = newPoints;
        root = buildTree(points, 0, points.size() - 1, 0);
    }
}

template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int dim) {
    Point<Dim> val = points[pivotIndex];
    std::swap(points[pivotIndex], points[right]);
    int index = left;
    for (int i = left; i < right; ++i) 
    {
        if (points[i][dim] < val[dim]) 
        {
            std::swap(points[i], points[index]);
            ++index;
        } 
        else if (points[i][dim] == val[dim] && points[i] < val) 
        {
            std::swap(points[i], points[index]);
            ++index;
        }
    }
    std::swap(points[index], points[right]);
    return index;
}

template<int Dim>
int KDTree<Dim>::select(vector<Point<Dim>>& points, int left, int right, int k, int dim) {
    while (left != right) 
    {
        int pivotIndex = partition(points, left, right, (left + right) / 2, dim);
        if (k == pivotIndex) 
        {
            return k;
        } 
        else if (k < pivotIndex) 
        {
            right = pivotIndex - 1;
        } 
        else 
        {
            left = pivotIndex + 1;
        }
    }
    return left;
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int left, int right, int dim) {
    if (left > right) 
    {
        return nullptr;
    }
    int mid = select(points, left, right, (left + right) / 2, dim);
    KDTreeNode* node = new KDTreeNode(points[mid]);
    node->left = buildTree(points, left, (mid - 1), ((dim + 1) % Dim));
    node->right = buildTree(points, (mid + 1), right, ((dim + 1) % Dim));
    return node;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) 
  { 
    clear(root);    
    size = rhs.size;
    root = copy(rhs.root); 
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* &subroot)
{
  if(subroot != nullptr)
  {
    clear(subroot->left);
    clear(subroot->right);
    delete subroot;
    subroot = nullptr;
  }
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if (root == nullptr) 
    {
        return Point<Dim>();
    }
    Point<Dim> closest = root->point;
    double bestDistance = distance(closest, query);
    int depth = 0;
    findNearestNeighborHelper(root, query, closest, bestDistance, depth);
    return closest;
}

template<int Dim>
void KDTree<Dim>::findNearestNeighborHelper(KDTreeNode* node, const Point<Dim>& query, Point<Dim>& closest, double& bestDistance, int depth) const
{
    if (node == nullptr) 
    {
        return;
    }
    double currDistance = distance(node->point, query);
    if (currDistance <= bestDistance) 
    {
        closest = node->point;
        bestDistance = currDistance;
    }
    int splitDim = depth % Dim;
    double axisDistance = node->point[splitDim] - query[splitDim];
    findNearestNeighborHelper(axisDistance < 0 ? node->right : node->left, query, closest, bestDistance, depth+1);
    if ((axisDistance * axisDistance) <= bestDistance)
    {
        findNearestNeighborHelper(axisDistance < 0 ? node->left : node->right, query, closest, bestDistance, depth+1);
    }
}

template<int Dim>
double KDTree<Dim>::distance(const Point<Dim>& a, const Point<Dim>& b) const
{
    double distance = 0;
    for (int i = 0; i < Dim; i++) 
    {
        distance += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return distance;
}


template<typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp) {
  if (start == end) 
  {
    return;
  }
  bool alwaysTrue = true;
  while(alwaysTrue)
  {
    RandIter pivot = start + (std::rand() % std::distance(start, end));
    RandIter left = start;
    RandIter right = end - 1;
    std::iter_swap(pivot, right);
    pivot = right;
    while (left < right)
    {
        if (cmp(*left, *pivot))
        {
          ++left;
        } 
        else 
        {
            std::iter_swap(left, --right);
        }
    }
    std::iter_swap(left, end - 1);
    pivot = left;
    if (pivot == k) 
    {
        break;
    } 
    else if (cmp(*k, *pivot)) 
    {
        end = pivot;
    } 
    else 
    {
        start = pivot + 1;
    }
  }
  return;
}

