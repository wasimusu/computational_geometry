def distance(a, b, c, d):
    return (d - b) ** 2 + (c - a) ** 2


def slope(a, b, c, d):
    if a == c:
        return float('inf')
    else:
        return (d - b) / (c - a)

def CF14C():

    infinity = 0
    zero = 0
    counter = {} # Sides counter
    points = set()
    for i in range(4):
        a, b, c, d = list(map(int, input().split()))
        points.add((a, b))
        points.add((c, d))
        s = slope(a, b, c, d)
        if s == float('inf'):
            infinity += 1
        elif s == 0:
            zero += 1
        side = distance(a, b, c, d)

        # No side has length zero in a rectangle
        if side == 0: return False

        counter[side] = counter.get(side, 0) + 1
    # If there are less than four points, it can't be rectangle
    if len(points) != 4: return False

    # There should be two sides parallel to x-axis and two sides parallel to y-axis
    if zero != 2 and infinity != 2: return False
    # print("Slopes ma problem vayena")

    # There should be only two values and both of them should have two elements
    if len(counter) > 2: return False
    # print("Sides pani duita equal cha")

    # Lets do the pythagoras test now. Final test.
    points = sorted(list(points), key = lambda x: (x[0], x[1]))
    a, b = points[0]
    c, d = points[1]
    e, f = points[2]
    g, h = points[3]

    sides = list(counter.keys())
    d1 = distance(a, b, c, d)
    d2 = distance(b, c, d, e)
    d3 = distance(a, b, e, f)
    if len(sides) > 1:
        if sides[0] + sides[1] != max(d1, d2, d3): return False
    else:
        if sides[0] * 2 != max(d1, d2, d3): return False

    # For everything else.
    return True

res = CF14C()
print("YES" if res else "NO")