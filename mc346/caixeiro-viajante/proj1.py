# Projeto de Python MC346 - 1s2015 - Caixeiro Viajante
# Dupla:
# Rodrigo Nagamine - RA: 137531
# Vinícius Andrade Frederico - RA: 139223

import math
cidades = []

class Cidade: # Facilitar organização
    def __init__(self, nome, x, y):
        self.nome = nome
        self.x  = float(x)
        self.y = float(y)

class memoriza:
  def __init__(self, function):
    self.function = function
    self.memorizado = {}

  def __call__(self, *args):
    try:
      return self.memorizado[args]
    except KeyError:
      self.memorizado[args] = self.function(*args)
      return self.memorizado[args]

def cidadeGen(cidades): # Gerador de permutações de cidades
    if len(cidades) == 0:
        yield []
    else:
        for i in range(len(cidades)): # Pra cada cidade
            for j in cidadeGen(cidades[:i] + cidades[i+1:]): # Gera lista removendo a cidade e adicionando-a depois
                if (not cidades[i] in j):
                    yield [cidades[i]] + j

@memoriza
def distancia(c1, c2): # Distancia euclidiana entre pontos
    return math.sqrt( (c1.x - c2.x)**2 + (c1.y - c2.y)**2 )

def lexComp(l1, l2):
    for i in range(len(l1)):
        if l1[i].nome < l2[i].nome:
            return True
        elif l1[i].nome > l2[i].nome:
            return False
    return False

# Trata entrada
cidadeExploded = input().split()
while(len(cidadeExploded) > 1):
    cidades.append(Cidade(cidadeExploded[0], cidadeExploded[1],cidadeExploded[2]))
    cidadeExploded = input().split()

# Pega a origem
for c in cidades:
    if c.nome == cidadeExploded[0]:
        origem = c
        cidades.remove(c)

g = cidadeGen(cidades)
menorCaminho = None
menorCaminhoDist = 0
for l in g:
    # Calcula distancia
    d = distancia(origem, l[0])
    for i in range(1, len(l)):
        d = d + distancia(l[i-1],l[i])
    d = d + distancia(origem, l[-1])
    d = math.ceil(d*10)/10

    # Se menor
    if menorCaminho is None or (d < menorCaminhoDist or (d == menorCaminhoDist and lexComp(l, menorCaminho)) ):
        menorCaminho = l
        menorCaminhoDist = d

# Imprime saída
print(origem.nome)
for c in menorCaminho:
    print(c.nome)
print(origem.nome)
print(str(menorCaminhoDist))