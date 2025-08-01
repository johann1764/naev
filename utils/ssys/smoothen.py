# python3


from geometry import vec

def smoothen( pos, neigh, hard = False ):
   newp = dict()
   for i in pos:
      for j in neigh[i]:
         if i not in neigh[j]:
            neigh[i].add(j)
   for k in pos:
      if (n := len(neigh[k])) > 1:
         acc, count = (vec(), count) if hard else (pos[k], 1)
         for s in neigh[k]:
            if N := [pos[i] for i in neigh[s] if i != k]:
               acc += 1.5*pos[s] - 0.5*sum(N, vec())/len(N)
            else:
               acc += pos[s]
            count += 1
         newp[k] = acc / count
   return newp

from math import sqrt
def circleify( pos, L, center ):
   newp = dict()
   # global approach -> more brutal
   V = [(pos[i] - pos[center]).size() for i in L]
   avg = sum(V) / len(V)
   for i in L:
      p = pos[center] + (pos[i]-pos[center]).normalize(avg)
      pos[i] = (pos[i] + 2.0*p) / 3.0
   """
   # local approach
   for i, j, k in zip(L[:-2],L[1:-1],L[2:]):
      c = (pos[i] + pos[k]) / 2.0
      v1, v2 = pos[i] - pos[center], pos[k] - pos[center]
      #avg = lambda x, y: (x + y) / 2.0
      avg = lambda x, y: sqrt(x * y)
      newp[j] = pos[center] + (pos[j] - pos[center]).normalize(avg(v1.size(), v2.size()))
   """
   return newp
