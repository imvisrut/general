import math

def square_and_multiply(a, x, n):
    y = 1
    x = bin(x)[2:]
    x_len = len(x)
    i = x_len - 1
    
    while i >= 0:
        if x[i] == '1':
            y = ((a * y) % n)
        a = ((a * a) % n)
        i -= 1
    return y

# (7**17) % 17
# print(square_and_multiply(7, 17, 97))

def find_mod_inv(a, m):
    for x in range(1, m):
        if( ( (a % m) * (x % m) % m) == 1):
            return x
    raise Exception('The modular inverse does not exist.')    

def get_coprime(n):
    for i in range(2, n):
        if math.gcd(i, n) == 1:
            return i

def RSA_GetKeys(p, q):
    n = p * q
    fi_n = (p - 1)*(q - 1)
    e = get_coprime(fi_n)
    d = find_mod_inv(e, fi_n)
    return {
        "pk" : e,
        "pr" : d
    }

def EncryptWithPublicKey(plainText, pk):
    _enc = ""
    for char in plainText:
        _char = square_and_multiply(ord(char), pk, 26)
        _enc += chr(_char + 97)
    return _enc
    
def DecryptWithPrivateKey(encText, pr):
    _dec = ""
    for char in encText:
        _char = square_and_multiply(ord(char), pr, 26)
        _dec += chr(_char + 97)
    return _dec

if __name__ == '__main__':
    # p = 39821
    # q = 504151
    p = 17
    q = 41
    
    keys = RSA_GetKeys(p, q)
    print(EncryptWithPublicKey("visrut", keys["pk"]))
    print(DecryptWithPrivateKey("obfmnm", keys["pr"]))
