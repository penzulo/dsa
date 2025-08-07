use std::cmp::Ordering;

pub fn linearsearch<T: PartialEq>(arr: &[T], target: T) -> i32 {
    match arr.iter().position(|val| *val == target) {
        Some(index) => index as i32,
        None => -1,
    }
}

pub fn binarysearch<T: PartialEq + PartialOrd>(
    sorted_arr: &[T],
    target: T,
) -> Result<usize, usize> {
    if sorted_arr.len() <= 0 {
        return Err(0);
    };

    let mut low: usize = 0;
    let mut high: usize = sorted_arr.len() - 1;
    let mut mid: usize;

    while low <= high {
        mid = low + (high - low) / 2;
        match sorted_arr[mid].partial_cmp(&target) {
            Some(Ordering::Equal) => return Ok(mid),
            Some(Ordering::Less) => low = mid + 1,
            Some(Ordering::Greater) => {
                if mid == 0 {
                    return Err(0);
                }
                high = mid - 1;
            }
            None => break,
        }
    }
    return Err(low);
}
