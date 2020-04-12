

def f(x,s):
    return pow(x,s)/(s+1)

def rectangle(a,b,h,s):
    n = (b - a) / h
    area = 0
    x = a + h
    for i in range(int(n)):
        area += h * f(x*(i-0.5),s)
    return area

def trapeze(a,b,h,s):
    n = (b - a) / h
    area = 0
    x = a + h
    area += h * (f(a,s) + f(b,s))/2
    for i in range(int(n-1)):
        area += h * f(x*i,s)
    return area

def simpson(a,b,h,s):
    n = (b - a) / h
    area = 0
    x = a + h
    area += h * (f(a,s) + f(b,s))/6 
    for i in range(int(n)):
        area += 2/3 * h * f(x*(i-0.5),s)
    for i in range(int(n-1)):
        area += 1/3 * h * f(x*i,s)
    return area





a = 0
b = 1
h = 0.0001
s = 0
I_rect = 0
I_trapz = 0
I_simpson = 0

I_rect2 = 0
I_trapz2 = 0
I_simpson2 = 0

k = 100
for i in range(k):
    I_rect += pow(-1,i) * rectangle(a,b,h,s)
    I_trapz += pow(-1,i) * trapeze(a,b,h,s)
    I_simpson += pow(-1,i) * simpson(a,b,h,s)
    
    I_rect2 += pow(-1,i) * rectangle(a,b,2*h,s)
    I_trapz2 += pow(-1,i) * trapeze(a,b,2*h,s)
    I_simpson2 += pow(-1,i) * simpson(a,b,2*h,s)
    s += 2
print("Rect = ",I_rect," ",I_rect2  - I_rect)
print("Trapez = ",I_trapz," ",I_trapz2 - I_trapz)
print("Simpson = ",I_simpson," ",I_simpson2 - I_simpson )
