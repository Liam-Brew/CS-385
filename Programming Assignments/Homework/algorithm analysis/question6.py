# Determines the integral values for which an algorithm of runtime 4n^3 seconds beats an
# algorithm of runtime 64nlgn seconds.


def functionA(n):
    # 4n^3
    counter = 0
    for i in range(0, 4):
        for j in range(0, n):
            for k in range(0, n):
                for l in range(0, n):
                    counter += 1
                    l += 1
                k += 1
            j += 1
        i += 1
    return counter


def functionB(n):
    # 64nlgn
    counter = 0
    for i in range(0, 64):
        for j in range(0, n):
            k = 1
            while k < n:
                counter += 1
                k *= 2
            j += 1
        i += 1
    return counter


if __name__ == "__main__":
    n = 0
    for n in range(0, 100):
        if functionA(n) < functionB(n):
            print(n)
