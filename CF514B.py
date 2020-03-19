"""
Han Solo and Lazer Gun
Given  a center, find out line pairs are there
"""


def slope(cx, cy, x, y):
    dx = cx - x
    if dx != 0:
        return (cy - y) / dx
    else:
        return float('inf')


def CF514B():
    N, cx, cy = list(map(int, input().split()))
    slopes = set()
    for i in range(N):
        x, y = list(map(int, input().split()))
        slopes.add(slope(cx, cy, x, y))
    return len(slopes)


if __name__ == '__main__':
    result = CF514B()
    print(result)