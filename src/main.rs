mod algorithms;

fn main() {
    let mut numbers = vec![12, 53, 235, 725, 5, 75, 35];
    println!("Original Array: {:?}", numbers);
    algorithms::sorting::sort::mergesort(&mut numbers);
    println!("Sorted Array: {:?}", numbers);
}

#[cfg(test)]
mod tests {
    use crate::algorithms::searching::search;

    #[test]
    fn test_binary_search_success() {
        let sorted_arr: Vec<i32> = (1..=10_000).collect();
        let target: i32 = 231;
        assert_eq!(search::binarysearch(&sorted_arr, target), Ok(230)) // Expected index is 230
    }

    #[test]
    fn test_binary_search_failure() {
        let sorted_arr: Vec<i32> = (1..=10_000).collect();
        let target: i32 = 0;
        assert_eq!(search::binarysearch(&sorted_arr, target), Err(0)) // Expected index is 0
    }
}
