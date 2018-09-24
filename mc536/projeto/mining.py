import urllib2
import re
from neo4jrestclient.client import GraphDatabase
from pyquery import PyQuery

def readUrl(url):
    try:
        response = urllib2.urlopen(url, timeout=50)
        data = response.read()
        #print " - ", data
        return data
    except Exception, e:
        print e
        return ""


gdb = GraphDatabase("http://localhost:7474/db/data/")

query = "MATCH (a:Artista) WHERE a.nomeArtistico = '' return a.uri"

uris = gdb.query(q=query)

#uris = ['http://en.wikipedia.org/wiki/Escape_the_Fate']

for x in uris:
    uri = x[0]
    try:
        
        #print uri
        html = readUrl(uri)
        #print  PyQuery(html)('h1#firstHeading')
        #print html
        #print "Nome"
        nome = PyQuery(html)("h1#firstHeading").text()
        #print "Linhas"
        linhas = PyQuery(html)("table.infobox tr")

        for linha in linhas:
            label = PyQuery(linha)('th').text()

            if label == "Genres":
                generos = PyQuery(linha)('td').text().split(',')
            if label == "Origin":
                origin = PyQuery(linha)('td').text()
            if label == "Website":
                website = PyQuery(linha)('td').text()

        query = """MERGE (a:Artista {uri: '%s'}) 
        ON MATCH a
        SET a.nomeArtistico = \"%s\", a.origem = \"%s\", a.website=\"%s\"
        RETURN a.nomeArtistico""" % (uri, nome, origin, website)
        r = gdb.query(q=query)[0][0]

        for genero in generos:
            genero = re.sub(r'\[.*\]','', genero.lower()).strip()
            if genero != "":
                query = """MERGE (g:Genero {nome: '%s'}) 
                WITH g 
                MATCH (a:Artista) WHERE a.uri='%s' 
                CREATE UNIQUE (a)-[:PLAYS]->g  
                RETURN a.uri""" % (genero, uri)
                r = gdb.query(q=query)[0][0]

    except Exception, e:
        print "Error:", uri, e
