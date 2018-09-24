<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
		$client = new Client();

	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1))
		header('Location: login.php');

		error_reporting(E_ALL);
		
		$run = "" . 
"MATCH (n:Person)-[r:KNOWS]->(m:Person) " .
"WHERE n.usuario='{$_SESSION['usuario']}' " .
"AND m.usuario='{$_GET['usuario']}' " .
"DELETE r " .
"return n, m";
//echo $run;
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        header('Location: conhecidos.php');
?>