class PQ:
    def __init__(self):
        self.heap = [0]*100
        self.info = [0]*100
        self.n = 0

    def insert(self, v, x):
        self.n += 1
        i = self.n
        while True:
            if i == 1: break
            if v >= self.heap[int(i/2)]: break
            self.heap[i] = self.heap[int(i/2)]
            self.info[i] = self.info[int(i/2)]
            i = int(i/2)
        self.heap[i] = v
        self.info[i] = x

    def remove(self):
        x = self.info[1]
        temp_v = self.heap[self.n]
        temp_x = self.info[self.n]
        self.n -= 1
        i = 1
        j = 2
        while j <= self.n:
            if (j < self.n) and (self.heap[j] > self.heap[j+1]):
                j += 1
            if temp_v <= self.heap[j]: break
            self.heap[i] = self.heap[j]
            self.info[i] = self.info[j]
            i = j
            j *= 2
        self.heap[i] = temp_v
        self.info[i] = temp_x
        return x

    def isEmpty(self):
        if self.n == 0: return True
        else: return False

def index(c):
    if ord(c) == 32: return 0
    else: return (ord(c)-64)

def makeHuffman(t, m):
    for i in range(m):
        count[index(t[i])] += 1
    for i in range(27):
        if count[i]:
            pq.insert(count[i], i)
    i = 27
    while not pq.isEmpty():
        t1 = pq.remove()
        t2 = pq.remove()
        dad[i] = 0
        dad[t1] = i
        dad[t2] = -i
        count[i] = count[t1] + count[t2]
        if not pq.isEmpty():
            pq.insert(count[i], i)
        i += 1
    for k in range(27):
        i = x = 0
        j = 1
        if count[k]:
            q = dad[k]
            while q:
                if q < 0:
                    x += j
                    q = -q
                q = dad[q]
                j += j
                i += 1
        code[k] = x
        length[k] = i


def encode(t, m):
    huffman_code = ''
    for j in range(m):
        i = length[index(t[j])]
        while i > 0:
            huffman_code += str((code[index(t[j])] >> i - 1) & 1)
            i -= 1
    return huffman_code


def decode(data, count, dad):
    result =''
    reversed_dict = {}
    for i in range(27):
        k = i
        if i ==0:
            word = chr(32)
        else:
            word = chr(i+64)
        key = ''
        while dad[k] != 0:
            if dad[k]>0:
                key = '0'+key
            elif dad[k]<0:
                key = '1'+key
            k = abs(dad[k])

        reversed_dict[key] = word
        
    start_index = 0
    
    end_index = 1

    max_index = len(data)

    while start_index != max_index:
        if data[start_index : end_index] in reversed_dict:
            result += reversed_dict[data[start_index : end_index]]
            start_index = end_index
        end_index += 1

    return result

text = 'A SIMPLE STRING TO BE ENCODED USING A MINIMAL NUMBER OF BITS'
count = [0]*100
dad = [0]*100
length = [0]*27
code = [0]*27
M = len(text)
pq = PQ()
makeHuffman(text, M)
data = encode(text,M)
print(decode(encode(text,M),count,dad))
