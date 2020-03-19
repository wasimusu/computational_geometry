# referenced dukkha

def cross(i, j, k, b, cost):
    return (cost[i] - cost[j]) * (b[i] - b[k]) - (b[i] - b[j]) * (cost[i] - cost[k])


def dot(i, j, a, b, cost):
    return cost[j] + a[i] * b[j]


def CF319C():
    N = int(input())
    a = tuple(map(int, input().split()))
    b = tuple(map(int, input().split()))

    cost = [0] * N
    hull = [0] * N  # Make hull considering total minimum cost and charge of individual trees

    left = 0
    right = 1 # Index of items in hull
    for i in range(1, N):
        # Find the last cut tree which incurs minimum cost for ith tree
        while left + 1 < right and dot(i, hull[left], a, b, cost) >= dot(i, hull[left + 1], a, b, cost):
            # Only increase left when it decreases cutting cost
            left += 1

        cost[i] = dot(i, hull[left], a, b, cost)

        while right >= 2 and cross(hull[right], hull[right - 1], i, b, cost) >= 0:
            right -= 1

        right += 1
        hull[right] = i

    return cost[-1]


if __name__ == '__main__':
    res = CF319C()
    print(res)