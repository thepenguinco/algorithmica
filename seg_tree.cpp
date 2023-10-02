#include <iostream>

// Naive Segtree for Dynamic Prefix Sum
struct SegTree {
    int left_bound;
    int right_bound;
    int sum = 0;
    SegTree *left = nullptr;
    SegTree *right = nullptr;

    // Default Segtree constructor
    SegTree(int left_bound, int right_bound): left_bound(left_bound), right_bound(right_bound) {
        if (left_bound + 1 < right_bound) {
            int mid_point = (left_bound + right_bound) / 2;
            left = new SegTree(left_bound, mid_point);
            right = new SegTree(mid_point, right_bound);
        }
    } 

    // Segtree constructor over existing array
    SegTree(int left_bound, int right_bound, int arr[]): left_bound(left_bound), right_bound(right_bound) {
        if (left_bound + 1 == right_bound) {
            sum = arr[left_bound];
        }
        else {
            int mid_point = (left_bound + right_bound) / 2;
            left = new SegTree(left_bound, mid_point, arr);
            right = new SegTree(mid_point, right_bound, arr);
            sum = left->sum + right->sum;
        }
    } 

    // Performs a[index] += value
    void Add(int index, int value) {
        sum += value;
        if (left != nullptr) {
            if (value < left->right_bound) {
                left->Add(index, value);
            }
            else {
                right->Add(index, value);
            }
        }
    }

    // Sum of the first k elements
    int Sum(int k) {
        if (right_bound <= k) {
            return sum;
        }
        if (left_bound >= k) {
            return 0;
        }
        return left->Sum(k) + right->Sum(k);
    }

    // Sum of elements between left bound and right bound [left_bound, right_bound)
    int Sum(int left_bound, int right_bound) {
        // intersection of query
        if (this->left_bound >= left_bound && this->right_bound <= right_bound) {
            return sum;
        }
        // non intersection of query
        if (right_bound <= this->left_bound || left_bound >= this->right_bound) {
            return 0;
        }
        return left->Sum(left_bound, right_bound) + right->Sum(left_bound, right_bound);
    }

};

int main()
{
    int arr[16] = {13,-1,2,23,-4,231,13,5,2,-88,-52,0,4,90,3,-12};
    SegTree *tree = new SegTree(0, 16, arr);
    std::cout << tree->Sum(4) << std::endl;
    std::cout << tree->Sum(16) << std::endl;
    std::cout << tree->Sum(12) - tree->Sum(8) << std::endl;
    std::cout << tree->Sum(0, 2) << std::endl;
    return 0;
}