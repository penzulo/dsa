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
