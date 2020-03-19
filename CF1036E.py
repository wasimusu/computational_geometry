"""
1036E : Covered Points
Borrows primarily from : https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
"""

def gcd(a, b):
    return a if b == 0 else gcd(b, a % b)


def cross(x1, y1, x2, y2):
    return x1 * y2 - x2 * y1


def online(line, x, y):
    """ If the x and y are within the range of min and max of x and y's respectively
    then the points MAY lie on the line
    """
    a, b, c, d = line
    if min(a, c) <= x <= max(a, c) and min(b, d) <= y <= max(b, d):
        return True
    return False


def CF1036E():
    N = int(input())

    lines = []
    count = 0
    # Read input line segment and find the lines covered by each line segment
    for _ in range(N):
        x1, y1, x2, y2 = map(int, input().split())
        count += gcd(abs(x1 - x2), abs(y1 - y2)) + 1
        lines.append((x1, y1, x2, y2))

    # Deal with the intersecting points
    for i in range(N):
        d = set()  # Unique intersecting points
        for j in range(i+1, N):
            px, py, qx, qy = lines[i]
            rx, ry, sx, sy = lines[j]

            vecx = (px - qx, rx - sx)
            vecy = (py - qy, ry - sy)

            # Cross of two lines
            area = cross(vecx[0], vecx[1], vecy[0], vecy[1])

            # Parallel line has no intersecting points
            if area == 0: continue

            # Computation of the exact point
            # This has been referenced from : https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
            lineA = cross(px, py, qx, qy)
            lineB = cross(rx, ry, sx, sy)
            x = cross(lineA, lineB, vecx[0], vecx[1]) / area
            y = cross(lineA, lineB, vecy[0], vecy[1]) / area

            # Verify the points are good.
            # If the points are integers and lie of the lines they are valid.
            if not (x % 1 == 0 and y % 1 == 0): continue
            if not (online(lines[i], x, y) and online(lines[j], x, y)): continue

            d.add((x, y))

        count -= len(d)

    return count

if __name__ == '__main__':
    res = CF1036E()
    print(res)