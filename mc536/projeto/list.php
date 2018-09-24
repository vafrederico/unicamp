<?php
		error_reporting(E_ALL);
	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
    Everyman\Neo4j\Transport,
    Everyman\Neo4j\Node,
    Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Index\NodeIndex,
        Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Cypher;

	$client = new Client(new Transport('localhost', 7474));
	$queryTemplate = "MATCH (n:Person) RETURN n.uri LIMIT 25";
    $query = new Cypher\Query($client, $queryTemplate);
    $result = $query->getResultSet();
    #var_dump($query);
    #var_dump($result);
    #echo "Found ".count($result)." actors:\n";
    foreach($result as $row) {
        echo $row->offsetGet('n.uri') . "<br>";
         
    }

?>