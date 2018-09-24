<?php
		error_reporting(E_ALL);
		
	$xml = simplexml_load_file("person.xml");
	$f = fopen('queries.txt', 'w');
	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
		
/*$host = "sql2.lab.ic.unicamp.br";
$user = "mc536in20";
$password = "ohuigaet";
$database = "mc536indb20";

	$conn = mysql_connect($host,$user,$password);
	$db = mysql_select_db($database, $conn);*/
	$client = new Client();
	//$pessoaIndex = new NodeIndex($client, 'pessoa');
	foreach ($xml as $person) {
			
		
		$uri = $person['uri'];
		$usuario = str_replace('http://www.ic.unicamp.br/MC536/2013/2/', '', $uri);
		$nome = $person['name'];
		$natal = $person['hometown'];
		$run = "MERGE (p:Person {usuario: '$usuario'}) " .
				"ON CREATE p " .
					"SET p.nome = '$nome', p.natal = '$natal'" .
				"RETURN p; ";
		
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
		
		//fwrite($f, $run . '\\r\\n');
		//$pessoa = $client->makeNode()->setProperty('nome', $nome)->setProperty('natal', $natal)->setProperty('uri', $uri)->save();
		//$pessoaIndex->add($pessoa, 'uri', $uri);
		//$query = "INSERT INTO `PESSOAS` VALUES ('$uri', '$nome', '$natal')";
		//mysql_query($query);

	}



	$xml = simplexml_load_file("knows.xml");

	foreach ($xml as $knows) {
		
		$person =  str_replace('http://www.ic.unicamp.br/MC536/2013/2/', '',utf8_decode($knows['person']));
		$colleague =  str_replace('http://www.ic.unicamp.br/MC536/2013/2/', '',utf8_decode($knows['colleague']));
		$run = "" . 
"MATCH (n:Person), (m:Person) " .
"WHERE n.usuario='$person' " .
"AND m.usuario='$colleague' " .
"CREATE UNIQUE n-[:KNOWS]->m " .
"return n, m";
		
		//fwrite($f, $run . '\\r\\n');
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
		
		 
	}
	


	$xml = simplexml_load_file("likesMusic.xml");

	foreach ($xml as $likes) {
		$person =  str_replace('http://www.ic.unicamp.br/MC536/2013/2/', '',utf8_decode($likes['person']));
		$colleague = strtolower(utf8_decode($likes['colleague']));
		echo $person . "-->" . $colleague . "<br>";
		$pais = "";
		$genero = "";
		$nomeArtistico = "";
		$rating = utf8_decode($likes['rating']);

		$run = "" .
"MERGE (a:Artista {uri: '$colleague'}) " .
"ON CREATE a " .
"SET a.nomeArtistico = '$nomeArtistico', a.pais = '$pais', a.genero='$genero'" .
"RETURN a; ";
		//fwrite($f, $run . '\\r\\n');
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
		
		$run = "" . 
"MATCH (n:Person), (m:Artista) " .
"WHERE n.usuario='$person' " .
"AND m.uri='$colleague' " .
"CREATE UNIQUE n-[:LIKES{rating: $rating}]->m " .
"return n, m";
		//fwrite($f, $run . '\\r\\n');
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
		
		 
		
	}
	
/*MATCH (p2:Person)-[:LIKES]->(a2:Artista)<-[:LIKES]-(p1:Person)
WHERE p1.uri='http://www.ic.unicamp.br/MC536/2013/2/brunovilar' with DISTINCT p2, p1, collect(a2.uri) as comum
MATCH (a:Artista)<-[r:LIKES]-p2 WHERE NOT p1-[:LIKES]->a
RETURN lower(a.uri) as uri, avg(r.rating)*(count(r.rating)+SUM(CASE (p2)<-[:KNOWS]-(p1)
	WHEN true THEN 1
	ELSE 0
END)) as score
ORDER BY score DESC*/

/*MATCH (p2:Person)-[:LIKES]->(a2:Artista)<-[:LIKES]-(p1:Person)
WHERE p1.uri='http://www.ic.unicamp.br/MC536/2013/2/brunovilar' with DISTINCT p2, p1, count(a2.uri) as comum
MATCH (a:Artista)<-[r:LIKES]-p2 WHERE NOT p1-[:LIKES]->a
RETURN lower(a.uri) as uri, avg(r.rating*comum)*(count(r.rating)+SUM(CASE (p2)<-[:KNOWS]-(p1)
	WHEN true THEN 1
	ELSE 0
END)) as score
ORDER BY score DESC*/
?>
