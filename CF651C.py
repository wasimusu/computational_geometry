""" Watchmen """


def block(arr, index):
    ref = arr[0][index]
    count = 0
    pairs = 0
    for i, num in enumerate(arr):
        if i < len(arr) - 1 and num[index] == ref:
            count += 1
        else:
            if i == len(arr) - 1 and num[index] == ref: count += 1
            pairs = pairs + count * (count - 1) // 2
            ref = num[index]
            count = 1
    return pairs


def CF651C():
    """ Count the number of pair of points for which euclidean and manhattan distance are equal """
    # Read input
    N = int(input())
    points = [tuple(map(int, input().split())) for _ in range(N)]

    # Sorted by x
    points = sorted(points)

    # Compute the number of duplicates
    pairs = 0
    rx, ry = points[0]
    curr = 0
    for i, (x, y) in enumerate(points):
        if i < N - 1 and rx == x and ry == y:
            curr += 1
        else:
            if i == N - 1 and rx == x and ry == y:
                curr += 1
            pairs -= curr * (curr - 1) // 2
            curr = 1
            rx, ry = x, y

    pairs += block(points, 0)  # Count points with same x

    # sorted by y
    points = sorted(points, key=lambda x: x[1])
    pairs += block(points, 1)
    return pairs


if __name__ == '__main__':
    result = CF651C()
    print(result)