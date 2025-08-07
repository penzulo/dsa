use std::cmp::Ordering;

// NOTE: Bubble Sort Implementation
pub fn bubblesort<T: Ord>(arr: &mut [T]) {
    let n = arr.len();
    let mut swapped: bool;

    for i in 0..n {
        swapped = false;
        for j in 0..n - 1 - i {
            if arr[j] > arr[j + 1] {
                arr.swap(j, j + 1);
                swapped = true;
            }
        }

        if !swapped {
            break;
        }
    }
}

// NOTE: Quick Sort implementation
pub fn quicksort<T: Ord>(arr: &mut [T]) {
    let len = arr.len();
    if len > 1 {
        _quicksort(arr, 0, len - 1);
    }
}

fn _quicksort<T: Ord>(arr: &mut [T], start: usize, end: usize) {
    if start >= end {
        return;
    }

    let pivot_idx = partition(arr, start, end);
    _quicksort(arr, start, pivot_idx - 1);
    _quicksort(arr, pivot_idx + 1, end);
}

fn partition<T: Ord>(arr: &mut [T], start: usize, end: usize) -> usize {
    let pivot_idx = start + (end - start) / 2;
    arr.swap(pivot_idx, end);
    let mut i = start;
    for j in start..end {
        if arr[j] <= arr[end] {
            arr.swap(i, j);
            i += 1;
        }
    }
    arr.swap(i, end);
    i
}

// NOTE: Merge Sort Implementation
pub fn mergesort<T: Ord + Clone>(arr: &mut [T]) {
    let len = arr.len();
    if len > 1 {
        let mid = len / 2;
        _mergesort(arr, 0, mid, len - 1);
    }
}

fn _mergesort<T: Ord + Clone>(arr: &mut [T], low: usize, mid: usize, high: usize) {
    if low < high {
        _mergesort(arr, low, (low + mid) / 2, mid);
        _mergesort(arr, mid + 1, (mid + 1 + high) / 2, high);
        merge(arr, low, mid, high);
    }
}

fn merge<T: Ord + Clone>(arr: &mut [T], low: usize, mid: usize, high: usize) {
    let mut i = low;
    let mut j = mid + 1;
    let mut combined: Vec<T> = Vec::with_capacity(high - low + 1);

    while i <= mid && j <= high {
        match arr[i].cmp(&arr[j]) {
            Ordering::Less => {
                combined.push(arr[i].clone());
                i += 1;
            }
            Ordering::Greater => {
                combined.push(arr[j].clone());
                j += 1;
            }
            Ordering::Equal => {
                combined.push(arr[i].clone());
                combined.push(arr[j].clone());
                i += 1;
                j += 1;
            }
        }
    }

    // Push any remaining elements from the left subarray
    while i <= mid {
        combined.push(arr[i].clone());
        i += 1;
    }

    // Push any remaining elements from the right subarray
    while j <= high {
        combined.push(arr[j].clone());
        j += 1;
    }

    for (idx, val) in combined.iter().enumerate() {
        arr[low + idx] = val.clone();
    }
}
