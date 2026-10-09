bool Search2D(int **nums, int m, int n, int k) {
    return Search1D((int *) nums, 0, m*n-1, k);
}

bool Search1D(int *nums, int left, int right, int k) {
    if (left > right){
        return false;
    }
    int mid = (left + right) / 2;
    if (nums[mid] == k){
        return true;
    }
    else if (k < nums[mid]){
        return Search1D(nums, left,  mid - 1, k);
    }
    else{
        return Search1D(nums, mid + 1, right, k);
    }
}

