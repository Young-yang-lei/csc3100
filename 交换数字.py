def swap(a, b):
    tmp = a
    a = b
    b = tmp
    return a,b

a = 5
b = 10
print(swap(a, b))
print(a,b)

def swap2(a, b):
    return b, a

a, b = 5, 10
print(swap2(a, b))
print(a,b)

'''如何真正交换两个数的大小'''
#def swap_true(a, b):
    