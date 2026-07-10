def linear_search(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i
    return -1

if __name__ == "__main__":
    arr = [10, 20, 122, 14, 123, 32]
    target = 14

    result = linear_search(arr, target)

    if result != -1:
        print(f"Element found at index {result}")
    else:
        print("Element not found in the array.")

print("jidkfsjklfnewdsfgrjlhnio")